<?xml version="1.0"?>
<xsl:stylesheet
   version='1.0'
   xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
>

<xsl:output method="text" indent="no" encoding="US-ASCII"/>

<xsl:template match="/"> 
<xsl:text>set terminal png size 1024,768
set output "container.png"
set title "Unique services per container type"

my_width=0.2

set style line 1 lt 1 lw 50
set style fill solid border -1
set xtics 2
set boxwidth my_width
set xtic nomirror rotate

</xsl:text>

 <xsl:text>set xtics (</xsl:text>
 <xsl:for-each select="container-report/entry">
      <xsl:text>&quot;</xsl:text>
      <xsl:value-of select="start-date"/>
      <xsl:text>&quot; </xsl:text><xsl:number value="position()"/>
      <xsl:if test="not(position() = last())"><xsl:text>, </xsl:text></xsl:if>
 </xsl:for-each>
 <xsl:text>)</xsl:text>

<xsl:text>
plot 'container.data.gnuplot' using 1:2 title "all containers" with boxes fs pattern 1,'container.data.gnuplot' using ($1+my_width):3 title "standalone container" with boxes fs pattern 2,'container.data.gnuplot' using ($1+2*my_width):4 title "servlet container" with boxes fs pattern 3
</xsl:text>

</xsl:template>

</xsl:stylesheet>
