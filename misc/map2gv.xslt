<?xml version="1.0" encoding="ISO-8859-1"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                xmlns:exsl="http://exslt.org/common"
                extension-element-prefixes="exsl"
                version="1.0">
<xsl:output method="text" omit-xml-declaration="yes"/>

<xsl:template match="/">
  <xsl:for-each select="egg-map/phrase-map/phrase">

    <xsl:text>digraph "</xsl:text>
		<xsl:value-of select="./name"/>
    <xsl:text>" {</xsl:text>
    <xsl:text>&#10;</xsl:text>

    <xsl:text>  compound=true;&#10;</xsl:text>

    <xsl:text>  rankdir=LR;&#10;</xsl:text>

    <xsl:text>  p [ label="</xsl:text>
    <xsl:value-of select="./name"/>
    <xsl:text>",&#10;</xsl:text>

    <xsl:text>      shape=box,&#10;</xsl:text>
    <xsl:text>      fillcolor=lightblue,&#10;</xsl:text>
    <xsl:text>      style="bold,filled,rounded"&#10;</xsl:text>
    <xsl:text>    ];&#10;</xsl:text>

		<xsl:for-each select="./sequence">

    <xsl:variable name="clusterPos">
      <xsl:number/>
    </xsl:variable>

		<xsl:text>  subgraph cluster</xsl:text>
    <xsl:value-of select="$clusterPos"/>
    <xsl:text>  {&#10;</xsl:text>

    <xsl:text>    shape=box;&#10;</xsl:text>

    <xsl:text>    fillcolor=lightyellow;&#10;</xsl:text>

    <xsl:text>    style="solid,filled,rounded";&#10;</xsl:text>

    <xsl:for-each select="./item">
  
    <xsl:variable name="itemPos">
      <xsl:number/>
    </xsl:variable>

    <xsl:text>    i</xsl:text>
    <xsl:value-of select="$clusterPos"/>
    <xsl:value-of select="$itemPos"/>
    <xsl:text> [ </xsl:text>
    <xsl:text>label="</xsl:text>
    <xsl:choose>
      <xsl:when test="./phrase-name">
        <xsl:value-of select="./phrase-name"/>
      </xsl:when>
      <xsl:when test="./literal">
        <xsl:choose>
          <xsl:when test="./literal/@type='absolute'">
            <xsl:value-of select="./literal"/>
					</xsl:when>
          <xsl:when test="./literal/@type='string'">
            <xsl:text>'</xsl:text>
            <xsl:value-of select="./literal"/>
            <xsl:text>'</xsl:text>
          </xsl:when>
        </xsl:choose>
      </xsl:when>
    </xsl:choose>
    <xsl:text>", </xsl:text>
    <xsl:choose>
      <xsl:when test="./phrase-name">
				<xsl:text>shape=box, </xsl:text>
				<xsl:text>fillcolor=lightgray, </xsl:text>
      </xsl:when>
      <xsl:when test="./literal">
				<xsl:text>shape=oval, </xsl:text>
				<xsl:text>fillcolor=pink, </xsl:text>
      </xsl:when>
    </xsl:choose>
    <xsl:text>style="bold,filled,rounded"</xsl:text>
    <xsl:text> ];&#10;</xsl:text>

    </xsl:for-each>

    <xsl:for-each select="./item">

    <xsl:variable name="itemPos">
      <xsl:number/>
    </xsl:variable>

    <xsl:if test="following-sibling::*">
			<xsl:text>    i</xsl:text>
			<xsl:value-of select="$clusterPos"/>
			<xsl:value-of select="$itemPos"/>
			<xsl:text disable-output-escaping="yes"> -></xsl:text>
			<xsl:text> i</xsl:text>
			<xsl:value-of select="$clusterPos"/>
			<xsl:value-of select="$itemPos + 1"/>
      <xsl:text> [ arrowhead=none, </xsl:text>
      <xsl:text>headlabel="+", </xsl:text>
      <xsl:text>headport=w, </xsl:text>
      <xsl:text>labeldistance=1.75 ];</xsl:text>
      <xsl:text>&#10;</xsl:text>
    </xsl:if>

    </xsl:for-each>

		<xsl:text>  }&#10;</xsl:text>

		</xsl:for-each>

    <xsl:for-each select="./sequence">

    <xsl:variable name="clusterPos">
      <xsl:number/>
    </xsl:variable>

    <xsl:text>  p </xsl:text>
    <xsl:text disable-output-escaping="yes">-> </xsl:text>
    <xsl:text>i</xsl:text>
    <xsl:value-of select="$clusterPos"/>
    <xsl:text>1 </xsl:text>
    <xsl:text>[ </xsl:text>
    <xsl:if test="position() = 1">
      <xsl:text>weight=100, </xsl:text>
    </xsl:if>
    <xsl:text>lhead=cluster</xsl:text>
    <xsl:value-of select="$clusterPos"/>
    <xsl:text>, </xsl:text>
    <xsl:text>sametail=yes, </xsl:text>
    <xsl:text>arrowhead=none, </xsl:text>
    <xsl:text>tailport=e,</xsl:text>
    <xsl:text> headport=w</xsl:text>
    <xsl:text>];&#10;</xsl:text>

    </xsl:for-each>

    <xsl:text>}</xsl:text>
    <xsl:text>&#10;</xsl:text>

    <xsl:text>&#10;</xsl:text>

	</xsl:for-each>
</xsl:template>

</xsl:stylesheet>
