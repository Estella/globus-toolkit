#! /usr/bin/env perl
#
# Test to exercise the "3rd party transfer" functionality of the Globus
# FTP client library using URL caching.
#

use strict;
use POSIX;
use Test;
use FtpTestLib;

my $test_exec = './globus-ftp-client-caching-transfer-test';
my @tests;
my @todo;

my $gpath = $ENV{GLOBUS_LOCATION};

if (!defined($gpath))
{
    die "GLOBUS_LOCATION needs to be set before running this script"
}

my ($source_host, $source_file, $local_copy) = setup_remote_source();
my ($dest_host, $dest_file) = setup_remote_dest();

@INC = (@INC, "$gpath/lib/perl");

# Test #1-2. Basic functionality: Do two transfers of /etc/group to/from
# localhost (with and without a valid proxy) using URL caching.
# Compare the resulting file with the real file
# Success if program returns 0, files compare,
# and no core file is generated, or no valid proxy, and program returns 1.
sub basic_func
{
    my ($use_proxy) = (shift);
    my ($errors,$rc) = ("",0);
    my ($old_proxy);

    unlink('core');

    $old_proxy=$ENV{'X509_USER_PROXY'}; 
    if($use_proxy == 0)
    {
        $ENV{'X509_USER_PROXY'} = "/dev/null";
    }
    my $command = "$test_exec -s gsiftp://$source_host$source_file -d gsiftp://$dest_host$dest_file >/dev/null 2>&1";
    $rc = system($command) / 256;
    if(($use_proxy && $rc != 0) || (!$use_proxy && $rc == 0))
    {
        $errors .= "\n# Test exited with $rc. ";
    }
    if(-r 'core')
    {
        $errors .= "\n# Core file generated.";
    }
    if($use_proxy && $errors eq "")
    {
        my ($output) = get_remote_file($dest_host, $dest_file);
        $errors = compare_local_files($local_copy, $output);
        unlink($output);
    }

    if($errors eq "")
    {
        ok('success', 'success');
    }
    else
    {
        $errors = "\n# Test failed\n# $command\n# " . $errors;
        ok($errors, 'success');
    }
    if((!$use_proxy) && defined($old_proxy))
    {
	$ENV{'X509_USER_PROXY'} = $old_proxy;
    }
    elsif((!$use_proxy))
    {
        delete $ENV{'X509_USER_PROXY'};
    }
    
    clean_remote_file($dest_host, $dest_file);
}
push(@tests, "basic_func" . "(0);"); #Use invalid proxy
push(@tests, "basic_func" . "(1);"); #Use proxy

# Test #3: Bad URL: Do a 3rd party transfer of a using a non-existent
# file from localhost twice using URL caching.
# Success if program returns 1 and no core file is generated.
sub bad_url_src
{
    my ($errors,$rc) = ("",0);

    unlink('core');

    my $command = "$test_exec -s gsiftp://$source_host/no-such-file-here -d gsiftp://$dest_host$dest_file >/dev/null 2>&1";
    $rc = system($command) / 256;
    if($rc != 2)
    {
        $errors .= "\n# Test exited with $rc.";
    }
    if(-r 'core')
    {
        $errors .= "\n# Core file generated.";
    }

    if($errors eq "")
    {
        ok('success', 'success');
    }
    else
    {
        $errors = "\n# Test failed\n# $command\n# " . $errors;
        ok($errors, 'success');
    }
    
    clean_remote_file($dest_host, $dest_file);
}
push(@tests, "bad_url_src");

# Test #4: Bad URL: Do a 3rd party transfer of an unwritable location as the
# destination twice using URL caching.
# Success if program returns 1 and no core file is generated.
sub bad_url_dest
{
    my ($errors,$rc) = ("",0);

    my $command = "$test_exec -s gsiftp://$source_host$source_file -d gsiftp://$dest_host/no-such-file-here >/dev/null 2>&1";
    $rc = system($command) / 256;
    if($rc != 2)
    {
        $errors .= "\n# Test exited with $rc.";
    }
    if(-r 'core')
    {
        $errors .= "\n# Core file generated.";
    }

    if($errors eq "")
    {
        ok('success', 'success');
    }
    else
    {
        $errors = "\n# Test failed\n# $command\n# " . $errors;
        ok($errors, 'success');
    }
}
push(@tests, "bad_url_dest");

# Test #5-45: Do a simple transfer of /etc/group to/from localhost twice,
# using caching, and aborting at each possible position. Note that not all
# aborts may be reached.
# Success if no core file is generated for all abort points. (we could use
# a stronger measure of success here)
sub abort_test
{
    my ($errors,$rc) = ("", 0);
    my ($abort_point) = shift;

    unlink('core');

    my $command = "$test_exec -a $abort_point -s gsiftp://$source_host$source_file -d gsiftp://$dest_host$dest_file >/dev/null 2>&1";
    $rc = system($command) / 256;
    if(-r 'core')
    {
        $errors .= "\n# Core file generated.";
    }

    if($errors eq "")
    {
        ok('success', 'success');
    }
    else
    {
        $errors = "\n# Test failed\n# $command\n# " . $errors;
        ok($errors, 'success');
    }
    
    clean_remote_file($dest_host, $dest_file);
}
for(my $i = 1; $i <= 41; $i++)
{
    push(@tests, "abort_test($i);");
}

# Test #46-86. Restart functionality: Do a simple transfer of /etc/group
# to/from localhost twice using URL caching, restarting at each
# plugin-possible point. Compare the resulting file with the real file.
# Success if program returns 0, files compare,
# and no core file is generated.
sub restart_test
{
    my ($errors,$rc) = ("",0);
    my ($restart_point) = shift;

    unlink('core');

    my $command = "$test_exec -r $restart_point -s gsiftp://$source_host$source_file -d gsiftp://$dest_host$dest_file >/dev/null 2>&1";
    $rc = system($command) / 256;
    if($rc != 0)
    {
        $errors .= "\n# Test exited with $rc. ";
    }
    if(-r 'core')
    {
        $errors .= "\n# Core file generated.";
    }
    if($errors eq "")
    {
        my ($output) = get_remote_file($dest_host, $dest_file);
        $errors = compare_local_files($local_copy, $output);
        unlink($output);
    }

    if($errors eq "")
    {
        ok('success', 'success');
    }
    else
    {
        $errors = "\n# Test failed\n# $command\n# " . $errors;
        ok($errors, 'success');
    }
    
    clean_remote_file($dest_host, $dest_file);
}
for(my $i = 1; $i <= 41; $i++)
{
    push(@tests, "restart_test($i);");
}

if(@ARGV)
{
    plan tests => scalar(@ARGV);

    foreach (@ARGV)
    {
        eval "&$tests[$_-1]";
    }
}
else
{
    plan tests => scalar(@tests), todo => \@todo;

    foreach (@tests)
    {
        eval "&$_";
    }
}
