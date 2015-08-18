<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.2.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.25" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.05" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="Fridge">
<packages>
</packages>
<symbols>
<symbol name="A-STUD">
<wire x1="0" y1="0" x2="38.1" y2="0" width="0.254" layer="97"/>
<wire x1="38.1" y1="0" x2="38.1" y2="38.1" width="0.254" layer="97"/>
<wire x1="38.1" y1="38.1" x2="0" y2="38.1" width="0.254" layer="97"/>
<wire x1="0" y1="38.1" x2="0" y2="0" width="0.254" layer="97"/>
<text x="9.398" y="9.652" size="25.4" layer="97">a</text>
</symbol>
<symbol name="B-STUD">
<wire x1="0" y1="0" x2="19.05" y2="0" width="0.254" layer="97"/>
<wire x1="19.05" y1="0" x2="19.05" y2="38.1" width="0.254" layer="97"/>
<wire x1="19.05" y1="38.1" x2="0" y2="38.1" width="0.254" layer="97"/>
<wire x1="0" y1="38.1" x2="0" y2="0" width="0.254" layer="97"/>
<text x="4.826" y="12.446" size="12.7" layer="97">b</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="A-STUD">
<gates>
<gate name="G$1" symbol="A-STUD" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="B-STUD">
<gates>
<gate name="G$1" symbol="B-STUD" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="U$1" library="Fridge" deviceset="A-STUD" device=""/>
<part name="U$2" library="Fridge" deviceset="B-STUD" device=""/>
<part name="U$3" library="Fridge" deviceset="B-STUD" device=""/>
<part name="U$4" library="Fridge" deviceset="A-STUD" device=""/>
<part name="U$5" library="Fridge" deviceset="B-STUD" device=""/>
<part name="U$6" library="Fridge" deviceset="B-STUD" device=""/>
<part name="U$7" library="Fridge" deviceset="A-STUD" device=""/>
<part name="U$8" library="Fridge" deviceset="B-STUD" device=""/>
<part name="U$9" library="Fridge" deviceset="B-STUD" device=""/>
<part name="U$10" library="Fridge" deviceset="A-STUD" device=""/>
<part name="U$11" library="Fridge" deviceset="B-STUD" device=""/>
<part name="U$12" library="Fridge" deviceset="B-STUD" device=""/>
<part name="U$13" library="Fridge" deviceset="B-STUD" device=""/>
<part name="U$14" library="Fridge" deviceset="B-STUD" device=""/>
<part name="U$15" library="Fridge" deviceset="B-STUD" device=""/>
<part name="U$16" library="Fridge" deviceset="B-STUD" device=""/>
<part name="U$17" library="Fridge" deviceset="B-STUD" device=""/>
<part name="U$18" library="Fridge" deviceset="B-STUD" device=""/>
<part name="U$19" library="Fridge" deviceset="B-STUD" device=""/>
<part name="U$20" library="Fridge" deviceset="B-STUD" device=""/>
<part name="U$21" library="Fridge" deviceset="B-STUD" device=""/>
<part name="U$22" library="Fridge" deviceset="B-STUD" device=""/>
<part name="U$23" library="Fridge" deviceset="B-STUD" device=""/>
<part name="U$24" library="Fridge" deviceset="B-STUD" device=""/>
</parts>
<sheets>
<sheet>
<plain>
<wire x1="0" y1="0" x2="0" y2="914.4" width="0.254" layer="97"/>
<wire x1="1849.12" y1="914.4" x2="1854.2" y2="914.4" width="0.254" layer="97"/>
<wire x1="1854.2" y1="914.4" x2="1854.2" y2="0" width="0.254" layer="97"/>
<wire x1="1849.12" y1="909.32" x2="1849.12" y2="914.4" width="0.254" layer="97"/>
<wire x1="0" y1="0" x2="5.08" y2="0" width="0.254" layer="97"/>
<wire x1="5.08" y1="0" x2="1849.12" y2="0" width="0.254" layer="97"/>
<wire x1="1849.12" y1="0" x2="1854.2" y2="0" width="0.254" layer="97"/>
<wire x1="0" y1="914.4" x2="5.08" y2="914.4" width="0.254" layer="97"/>
<wire x1="5.08" y1="914.4" x2="1849.12" y2="914.4" width="0.254" layer="97"/>
<wire x1="12.7" y1="-50.8" x2="12.7" y2="-63.5" width="0.254" layer="97"/>
<wire x1="12.7" y1="-63.5" x2="12.7" y2="-76.2" width="0.254" layer="97"/>
<wire x1="12.7" y1="-63.5" x2="1841.5" y2="-63.5" width="0.254" layer="97"/>
<wire x1="1841.5" y1="-63.5" x2="1841.5" y2="-76.2" width="0.254" layer="97"/>
<wire x1="1841.5" y1="-50.8" x2="1841.5" y2="-63.5" width="0.254" layer="97"/>
<wire x1="1841.5" y1="-63.5" x2="1828.8" y2="-50.8" width="0.254" layer="97"/>
<wire x1="1841.5" y1="-63.5" x2="1828.8" y2="-76.2" width="0.254" layer="97"/>
<wire x1="12.7" y1="-63.5" x2="25.4" y2="-50.8" width="0.254" layer="97"/>
<wire x1="12.7" y1="-63.5" x2="25.4" y2="-76.2" width="0.254" layer="97"/>
<wire x1="-50.8" y1="0" x2="-63.5" y2="0" width="0.254" layer="97"/>
<wire x1="-63.5" y1="0" x2="-76.2" y2="0" width="0.254" layer="97"/>
<wire x1="-76.2" y1="12.7" x2="-63.5" y2="0" width="0.254" layer="97"/>
<wire x1="-63.5" y1="0" x2="-50.8" y2="12.7" width="0.254" layer="97"/>
<wire x1="-63.5" y1="0" x2="-63.5" y2="914.4" width="0.254" layer="97"/>
<wire x1="-63.5" y1="914.4" x2="-76.2" y2="914.4" width="0.254" layer="97"/>
<wire x1="-63.5" y1="914.4" x2="-76.2" y2="901.7" width="0.254" layer="97"/>
<wire x1="-63.5" y1="914.4" x2="-50.8" y2="901.7" width="0.254" layer="97"/>
<wire x1="-63.5" y1="914.4" x2="-50.8" y2="914.4" width="0.254" layer="97"/>
<wire x1="-76.2" y1="38.1" x2="-88.9" y2="38.1" width="0.254" layer="97"/>
<wire x1="-88.9" y1="38.1" x2="-101.6" y2="38.1" width="0.254" layer="97"/>
<wire x1="-101.6" y1="50.8" x2="-88.9" y2="38.1" width="0.254" layer="97"/>
<wire x1="-88.9" y1="38.1" x2="-76.2" y2="50.8" width="0.254" layer="97"/>
<wire x1="-88.9" y1="38.1" x2="-88.9" y2="876.3" width="0.254" layer="97"/>
<wire x1="-88.9" y1="876.3" x2="-101.6" y2="876.3" width="0.254" layer="97"/>
<wire x1="-88.9" y1="876.3" x2="-101.6" y2="863.6" width="0.254" layer="97"/>
<wire x1="-88.9" y1="876.3" x2="-76.2" y2="863.6" width="0.254" layer="97"/>
<wire x1="-88.9" y1="876.3" x2="-76.2" y2="876.3" width="0.254" layer="97"/>
<wire x1="50.8" y1="-76.2" x2="50.8" y2="-88.9" width="0.254" layer="97"/>
<wire x1="50.8" y1="-88.9" x2="50.8" y2="-101.6" width="0.254" layer="97"/>
<wire x1="50.8" y1="-88.9" x2="1803.4" y2="-88.9" width="0.254" layer="97"/>
<wire x1="1803.4" y1="-88.9" x2="1803.4" y2="-101.6" width="0.254" layer="97"/>
<wire x1="1803.4" y1="-76.2" x2="1803.4" y2="-88.9" width="0.254" layer="97"/>
<wire x1="1803.4" y1="-88.9" x2="1790.7" y2="-76.2" width="0.254" layer="97"/>
<wire x1="1803.4" y1="-88.9" x2="1790.7" y2="-101.6" width="0.254" layer="97"/>
<wire x1="50.8" y1="-88.9" x2="63.5" y2="-76.2" width="0.254" layer="97"/>
<wire x1="50.8" y1="-88.9" x2="63.5" y2="-101.6" width="0.254" layer="97"/>
<text x="-45.72" y="431.8" size="12.7" layer="97" rot="R90">36.00"</text>
<text x="-96.52" y="431.8" size="12.7" layer="97" rot="R90">33.00"</text>
<text x="904.24" y="-114.3" size="12.7" layer="97">69.00"</text>
<text x="904.24" y="-50.8" size="12.7" layer="97">72.00"</text>
<wire x1="101.6" y1="838.2" x2="101.6" y2="76.2" width="12.7" layer="98"/>
<wire x1="101.6" y1="76.2" x2="635" y2="76.2" width="12.7" layer="98"/>
<wire x1="635" y1="76.2" x2="635" y2="838.2" width="12.7" layer="98"/>
<wire x1="635" y1="838.2" x2="101.6" y2="838.2" width="12.7" layer="98"/>
<wire x1="660.4" y1="838.2" x2="660.4" y2="76.2" width="12.7" layer="98"/>
<wire x1="660.4" y1="76.2" x2="1193.8" y2="76.2" width="12.7" layer="98"/>
<wire x1="1193.8" y1="76.2" x2="1193.8" y2="838.2" width="12.7" layer="98"/>
<wire x1="1193.8" y1="838.2" x2="660.4" y2="838.2" width="12.7" layer="98"/>
<wire x1="1219.2" y1="838.2" x2="1219.2" y2="76.2" width="12.7" layer="98"/>
<wire x1="1219.2" y1="76.2" x2="1752.6" y2="76.2" width="12.7" layer="98"/>
<wire x1="1752.6" y1="76.2" x2="1752.6" y2="838.2" width="12.7" layer="98"/>
<wire x1="1752.6" y1="838.2" x2="1219.2" y2="838.2" width="12.7" layer="98"/>
<text x="279.4" y="990.6" size="50.8" layer="97">Supercooler XY (cross section)</text>
<text x="13.97" y="-135.89" size="12.7" layer="97">a</text>
<wire x1="0" y1="-111.76" x2="38.1" y2="-111.76" width="0.1524" layer="97"/>
<wire x1="38.1" y1="-111.76" x2="38.1" y2="-149.86" width="0.1524" layer="97"/>
<wire x1="38.1" y1="-149.86" x2="0" y2="-149.86" width="0.1524" layer="97"/>
<wire x1="0" y1="-149.86" x2="0" y2="-111.76" width="0.1524" layer="97"/>
<text x="43.18" y="-144.78" size="12.7" layer="97">1.5x1.5" stud</text>
<wire x1="25.4" y1="-162.56" x2="38.1" y2="-162.56" width="0.1524" layer="97"/>
<wire x1="38.1" y1="-162.56" x2="38.1" y2="-187.96" width="0.1524" layer="97"/>
<wire x1="25.4" y1="-162.56" x2="25.4" y2="-193.04" width="0.1524" layer="97"/>
<wire x1="22.86" y1="-193.04" x2="27.94" y2="-193.04" width="0.1524" layer="97"/>
<wire x1="27.94" y1="-193.04" x2="33.02" y2="-190.5" width="0.1524" layer="97" curve="53.130102"/>
<wire x1="33.02" y1="-190.5" x2="38.1" y2="-187.96" width="0.1524" layer="97" curve="-53.130102"/>
<wire x1="38.1" y1="-187.96" x2="40.64" y2="-187.96" width="0.1524" layer="97"/>
<wire x1="22.86" y1="-195.58" x2="25.4" y2="-195.58" width="0.1524" layer="97"/>
<wire x1="25.4" y1="-195.58" x2="27.94" y2="-195.58" width="0.1524" layer="97"/>
<wire x1="27.94" y1="-195.58" x2="33.02" y2="-193.04" width="0.1524" layer="97" curve="53.130102"/>
<wire x1="33.02" y1="-193.04" x2="38.1" y2="-190.5" width="0.1524" layer="97" curve="-53.130102"/>
<wire x1="38.1" y1="-190.5" x2="40.64" y2="-190.5" width="0.1524" layer="97"/>
<wire x1="25.4" y1="-195.58" x2="25.4" y2="-210.82" width="0.1524" layer="97"/>
<wire x1="25.4" y1="-210.82" x2="38.1" y2="-210.82" width="0.1524" layer="97"/>
<wire x1="38.1" y1="-210.82" x2="38.1" y2="-190.5" width="0.1524" layer="97"/>
<text x="43.18" y="-182.88" size="12.7" layer="97">0.2" thick plywood</text>
<text x="472.44" y="-198.12" size="25.4" layer="97">external height=24"
internal hight=20"</text>
<text x="173.99" y="-137.16" size="12.7" layer="97">b</text>
<wire x1="170.18" y1="-111.76" x2="189.23" y2="-111.76" width="0.1524" layer="97"/>
<wire x1="189.23" y1="-111.76" x2="189.23" y2="-149.86" width="0.1524" layer="97"/>
<wire x1="189.23" y1="-149.86" x2="170.18" y2="-149.86" width="0.1524" layer="97"/>
<wire x1="170.18" y1="-149.86" x2="170.18" y2="-111.76" width="0.1524" layer="97"/>
<text x="200.66" y="-144.78" size="12.7" layer="97">0.75x1.5" stud</text>
<wire x1="5.08" y1="909.32" x2="1849.12" y2="909.32" width="0.254" layer="97"/>
<wire x1="5.08" y1="914.4" x2="5.08" y2="5.08" width="0.254" layer="97"/>
<wire x1="5.08" y1="5.08" x2="5.08" y2="0" width="0.254" layer="97"/>
<wire x1="5.08" y1="5.08" x2="1849.12" y2="5.08" width="0.254" layer="97"/>
<wire x1="1849.12" y1="5.08" x2="1849.12" y2="0" width="0.254" layer="97"/>
<wire x1="1849.12" y1="5.08" x2="1849.12" y2="909.32" width="0.254" layer="97"/>
<wire x1="43.18" y1="871.22" x2="48.26" y2="871.22" width="0.254" layer="97"/>
<wire x1="48.26" y1="871.22" x2="48.26" y2="866.14" width="0.254" layer="97"/>
<wire x1="48.26" y1="866.14" x2="48.26" y2="48.26" width="0.254" layer="97"/>
<wire x1="48.26" y1="48.26" x2="48.26" y2="43.18" width="0.254" layer="97"/>
<wire x1="48.26" y1="43.18" x2="43.18" y2="43.18" width="0.254" layer="97"/>
<wire x1="43.18" y1="43.18" x2="43.18" y2="871.22" width="0.254" layer="97"/>
<wire x1="1811.02" y1="871.22" x2="1805.94" y2="871.22" width="0.254" layer="97"/>
<wire x1="1805.94" y1="871.22" x2="1805.94" y2="866.14" width="0.254" layer="97"/>
<wire x1="1805.94" y1="866.14" x2="1805.94" y2="48.26" width="0.254" layer="97"/>
<wire x1="1805.94" y1="48.26" x2="1805.94" y2="43.18" width="0.254" layer="97"/>
<wire x1="1805.94" y1="43.18" x2="1811.02" y2="43.18" width="0.254" layer="97"/>
<wire x1="1811.02" y1="43.18" x2="1811.02" y2="871.22" width="0.254" layer="97"/>
<wire x1="48.26" y1="871.22" x2="1805.94" y2="871.22" width="0.254" layer="97"/>
<wire x1="1805.94" y1="866.14" x2="48.26" y2="866.14" width="0.254" layer="97"/>
<wire x1="48.26" y1="43.18" x2="1805.94" y2="43.18" width="0.254" layer="97"/>
<wire x1="1805.94" y1="48.26" x2="48.26" y2="48.26" width="0.254" layer="97"/>
<circle x="1536.7" y="1111.25" radius="45.7905" width="0.254" layer="97"/>
<wire x1="1504.95" y1="1143" x2="1568.45" y2="1079.5" width="0.254" layer="97"/>
<wire x1="1568.45" y1="1143" x2="1504.95" y2="1079.5" width="0.254" layer="97"/>
<text x="1593.85" y="1098.55" size="25.4" layer="97">UP</text>
<wire x1="1504.95" y1="1016" x2="1765.3" y2="1016" width="0.254" layer="97"/>
<wire x1="1765.3" y1="1016" x2="1720.85" y2="1035.05" width="0.254" layer="97"/>
<wire x1="1720.85" y1="1035.05" x2="1720.85" y2="996.95" width="0.254" layer="97"/>
<wire x1="1720.85" y1="996.95" x2="1765.3" y2="1016" width="0.254" layer="97"/>
<text x="1778" y="1003.3" size="25.4" layer="97">X</text>
</plain>
<instances>
<instance part="U$1" gate="G$1" x="5.08" y="871.22"/>
<instance part="U$2" gate="G$1" x="43.18" y="871.22"/>
<instance part="U$3" gate="G$1" x="43.18" y="852.17" rot="R90"/>
<instance part="U$4" gate="G$1" x="5.08" y="5.08"/>
<instance part="U$5" gate="G$1" x="43.18" y="5.08"/>
<instance part="U$6" gate="G$1" x="43.18" y="43.18" rot="R90"/>
<instance part="U$7" gate="G$1" x="1811.02" y="5.08"/>
<instance part="U$8" gate="G$1" x="1791.97" y="5.08"/>
<instance part="U$9" gate="G$1" x="1849.12" y="43.18" rot="R90"/>
<instance part="U$10" gate="G$1" x="1811.02" y="871.22"/>
<instance part="U$11" gate="G$1" x="1791.97" y="871.22"/>
<instance part="U$12" gate="G$1" x="1849.12" y="852.17" rot="R90"/>
<instance part="U$13" gate="G$1" x="688.34" y="5.08"/>
<instance part="U$14" gate="G$1" x="361.95" y="5.08"/>
<instance part="U$15" gate="G$1" x="1469.39" y="5.08"/>
<instance part="U$16" gate="G$1" x="1122.68" y="871.22"/>
<instance part="U$17" gate="G$1" x="741.68" y="871.22"/>
<instance part="U$18" gate="G$1" x="1477.01" y="871.22"/>
<instance part="U$19" gate="G$1" x="1849.12" y="605.79" rot="R90"/>
<instance part="U$20" gate="G$1" x="43.18" y="626.11" rot="R90"/>
<instance part="U$21" gate="G$1" x="43.18" y="302.26" rot="R90"/>
<instance part="U$22" gate="G$1" x="1849.12" y="275.59" rot="R90"/>
<instance part="U$23" gate="G$1" x="405.13" y="871.22"/>
<instance part="U$24" gate="G$1" x="1139.19" y="5.08"/>
</instances>
<busses>
</busses>
<nets>
</nets>
</sheet>
<sheet>
<plain>
<wire x1="0" y1="0" x2="0" y2="914.4" width="0.254" layer="97"/>
<wire x1="1854.2" y1="914.4" x2="1854.2" y2="0" width="0.254" layer="97"/>
<wire x1="0" y1="0" x2="1854.2" y2="0" width="0.254" layer="97"/>
<wire x1="0" y1="914.4" x2="1854.2" y2="914.4" width="0.254" layer="97"/>
<wire x1="12.7" y1="-50.8" x2="12.7" y2="-63.5" width="0.254" layer="97"/>
<wire x1="12.7" y1="-63.5" x2="12.7" y2="-76.2" width="0.254" layer="97"/>
<wire x1="12.7" y1="-63.5" x2="1841.5" y2="-63.5" width="0.254" layer="97"/>
<wire x1="1841.5" y1="-63.5" x2="1841.5" y2="-76.2" width="0.254" layer="97"/>
<wire x1="1841.5" y1="-50.8" x2="1841.5" y2="-63.5" width="0.254" layer="97"/>
<wire x1="1841.5" y1="-63.5" x2="1828.8" y2="-50.8" width="0.254" layer="97"/>
<wire x1="1841.5" y1="-63.5" x2="1828.8" y2="-76.2" width="0.254" layer="97"/>
<wire x1="12.7" y1="-63.5" x2="25.4" y2="-50.8" width="0.254" layer="97"/>
<wire x1="12.7" y1="-63.5" x2="25.4" y2="-76.2" width="0.254" layer="97"/>
<wire x1="-50.8" y1="0" x2="-63.5" y2="0" width="0.254" layer="97"/>
<wire x1="-63.5" y1="0" x2="-76.2" y2="0" width="0.254" layer="97"/>
<wire x1="-76.2" y1="12.7" x2="-63.5" y2="0" width="0.254" layer="97"/>
<wire x1="-63.5" y1="0" x2="-50.8" y2="12.7" width="0.254" layer="97"/>
<wire x1="-63.5" y1="0" x2="-63.5" y2="914.4" width="0.254" layer="97"/>
<wire x1="-63.5" y1="914.4" x2="-76.2" y2="914.4" width="0.254" layer="97"/>
<wire x1="-63.5" y1="914.4" x2="-76.2" y2="901.7" width="0.254" layer="97"/>
<wire x1="-63.5" y1="914.4" x2="-50.8" y2="901.7" width="0.254" layer="97"/>
<wire x1="-63.5" y1="914.4" x2="-50.8" y2="914.4" width="0.254" layer="97"/>
<wire x1="-76.2" y1="38.1" x2="-88.9" y2="38.1" width="0.254" layer="97"/>
<wire x1="-88.9" y1="38.1" x2="-101.6" y2="38.1" width="0.254" layer="97"/>
<wire x1="-101.6" y1="50.8" x2="-88.9" y2="38.1" width="0.254" layer="97"/>
<wire x1="-88.9" y1="38.1" x2="-76.2" y2="50.8" width="0.254" layer="97"/>
<wire x1="-88.9" y1="38.1" x2="-88.9" y2="876.3" width="0.254" layer="97"/>
<wire x1="-88.9" y1="876.3" x2="-101.6" y2="876.3" width="0.254" layer="97"/>
<wire x1="-88.9" y1="876.3" x2="-101.6" y2="863.6" width="0.254" layer="97"/>
<wire x1="-88.9" y1="876.3" x2="-76.2" y2="863.6" width="0.254" layer="97"/>
<wire x1="-88.9" y1="876.3" x2="-76.2" y2="876.3" width="0.254" layer="97"/>
<wire x1="50.8" y1="-76.2" x2="50.8" y2="-88.9" width="0.254" layer="97"/>
<wire x1="50.8" y1="-88.9" x2="50.8" y2="-101.6" width="0.254" layer="97"/>
<wire x1="50.8" y1="-88.9" x2="1803.4" y2="-88.9" width="0.254" layer="97"/>
<wire x1="1803.4" y1="-88.9" x2="1803.4" y2="-101.6" width="0.254" layer="97"/>
<wire x1="1803.4" y1="-76.2" x2="1803.4" y2="-88.9" width="0.254" layer="97"/>
<wire x1="1803.4" y1="-88.9" x2="1790.7" y2="-76.2" width="0.254" layer="97"/>
<wire x1="1803.4" y1="-88.9" x2="1790.7" y2="-101.6" width="0.254" layer="97"/>
<wire x1="50.8" y1="-88.9" x2="63.5" y2="-76.2" width="0.254" layer="97"/>
<wire x1="50.8" y1="-88.9" x2="63.5" y2="-101.6" width="0.254" layer="97"/>
<text x="-45.72" y="431.8" size="12.7" layer="97" rot="R90">36.00"</text>
<text x="-96.52" y="431.8" size="12.7" layer="97" rot="R90">33.00"</text>
<text x="904.24" y="-114.3" size="12.7" layer="97">69.00"</text>
<text x="904.24" y="-50.8" size="12.7" layer="97">72.00"</text>
<text x="279.4" y="990.6" size="50.8" layer="97">Supercooler XY (bottom, lid*)</text>
<text x="13.97" y="-135.89" size="12.7" layer="97">a</text>
<wire x1="0" y1="-111.76" x2="38.1" y2="-111.76" width="0.1524" layer="97"/>
<wire x1="38.1" y1="-111.76" x2="38.1" y2="-149.86" width="0.1524" layer="97"/>
<wire x1="38.1" y1="-149.86" x2="0" y2="-149.86" width="0.1524" layer="97"/>
<wire x1="0" y1="-149.86" x2="0" y2="-111.76" width="0.1524" layer="97"/>
<text x="43.18" y="-144.78" size="12.7" layer="97">1.5x1.5" stud</text>
<wire x1="25.4" y1="-162.56" x2="38.1" y2="-162.56" width="0.1524" layer="97"/>
<wire x1="38.1" y1="-162.56" x2="38.1" y2="-187.96" width="0.1524" layer="97"/>
<wire x1="25.4" y1="-162.56" x2="25.4" y2="-193.04" width="0.1524" layer="97"/>
<wire x1="22.86" y1="-193.04" x2="27.94" y2="-193.04" width="0.1524" layer="97"/>
<wire x1="27.94" y1="-193.04" x2="33.02" y2="-190.5" width="0.1524" layer="97" curve="53.130102"/>
<wire x1="33.02" y1="-190.5" x2="38.1" y2="-187.96" width="0.1524" layer="97" curve="-53.130102"/>
<wire x1="38.1" y1="-187.96" x2="40.64" y2="-187.96" width="0.1524" layer="97"/>
<wire x1="22.86" y1="-195.58" x2="25.4" y2="-195.58" width="0.1524" layer="97"/>
<wire x1="25.4" y1="-195.58" x2="27.94" y2="-195.58" width="0.1524" layer="97"/>
<wire x1="27.94" y1="-195.58" x2="33.02" y2="-193.04" width="0.1524" layer="97" curve="53.130102"/>
<wire x1="33.02" y1="-193.04" x2="38.1" y2="-190.5" width="0.1524" layer="97" curve="-53.130102"/>
<wire x1="38.1" y1="-190.5" x2="40.64" y2="-190.5" width="0.1524" layer="97"/>
<wire x1="25.4" y1="-195.58" x2="25.4" y2="-210.82" width="0.1524" layer="97"/>
<wire x1="25.4" y1="-210.82" x2="38.1" y2="-210.82" width="0.1524" layer="97"/>
<wire x1="38.1" y1="-210.82" x2="38.1" y2="-190.5" width="0.1524" layer="97"/>
<text x="43.18" y="-182.88" size="12.7" layer="97">0.2" thick plywood</text>
<text x="472.44" y="-198.12" size="25.4" layer="97">external height=24"
internal hight=20"</text>
<text x="173.99" y="-137.16" size="12.7" layer="97">b</text>
<wire x1="170.18" y1="-111.76" x2="189.23" y2="-111.76" width="0.1524" layer="97"/>
<wire x1="189.23" y1="-111.76" x2="189.23" y2="-149.86" width="0.1524" layer="97"/>
<wire x1="189.23" y1="-149.86" x2="170.18" y2="-149.86" width="0.1524" layer="97"/>
<wire x1="170.18" y1="-149.86" x2="170.18" y2="-111.76" width="0.1524" layer="97"/>
<text x="200.66" y="-144.78" size="12.7" layer="97">0.75x1.5" stud</text>
<wire x1="5.08" y1="909.32" x2="1849.12" y2="909.32" width="0.254" layer="97"/>
<wire x1="1849.12" y1="909.32" x2="1849.12" y2="871.22" width="0.254" layer="97"/>
<wire x1="1849.12" y1="871.22" x2="1811.02" y2="871.22" width="0.254" layer="97"/>
<wire x1="1811.02" y1="871.22" x2="1791.97" y2="871.22" width="0.254" layer="97"/>
<wire x1="1791.97" y1="871.22" x2="1402.08" y2="871.22" width="0.254" layer="97"/>
<wire x1="1402.08" y1="871.22" x2="1376.68" y2="871.22" width="0.254" layer="97"/>
<wire x1="1376.68" y1="871.22" x2="1014.73" y2="871.22" width="0.254" layer="97"/>
<wire x1="1014.73" y1="871.22" x2="995.68" y2="871.22" width="0.254" layer="97"/>
<wire x1="995.68" y1="871.22" x2="659.13" y2="871.22" width="0.254" layer="97"/>
<wire x1="659.13" y1="871.22" x2="640.08" y2="871.22" width="0.254" layer="97"/>
<wire x1="640.08" y1="871.22" x2="373.38" y2="871.22" width="0.254" layer="97"/>
<wire x1="373.38" y1="871.22" x2="354.33" y2="871.22" width="0.254" layer="97"/>
<wire x1="354.33" y1="871.22" x2="62.23" y2="871.22" width="0.254" layer="97"/>
<wire x1="62.23" y1="871.22" x2="43.18" y2="871.22" width="0.254" layer="97"/>
<wire x1="43.18" y1="871.22" x2="5.08" y2="871.22" width="0.254" layer="97"/>
<wire x1="5.08" y1="871.22" x2="5.08" y2="909.32" width="0.254" layer="97"/>
<wire x1="5.08" y1="5.08" x2="1849.12" y2="5.08" width="0.254" layer="97"/>
<wire x1="1849.12" y1="5.08" x2="1849.12" y2="43.18" width="0.254" layer="97"/>
<wire x1="1849.12" y1="43.18" x2="1811.02" y2="43.18" width="0.254" layer="97"/>
<wire x1="1811.02" y1="43.18" x2="1791.97" y2="43.18" width="0.254" layer="97"/>
<wire x1="1791.97" y1="43.18" x2="1402.08" y2="43.18" width="0.254" layer="97"/>
<wire x1="1402.08" y1="43.18" x2="1376.68" y2="43.18" width="0.254" layer="97"/>
<wire x1="1376.68" y1="43.18" x2="1014.73" y2="43.18" width="0.254" layer="97"/>
<wire x1="1014.73" y1="43.18" x2="995.68" y2="43.18" width="0.254" layer="97"/>
<wire x1="995.68" y1="43.18" x2="659.13" y2="43.18" width="0.254" layer="97"/>
<wire x1="659.13" y1="43.18" x2="640.08" y2="43.18" width="0.254" layer="97"/>
<wire x1="640.08" y1="43.18" x2="373.38" y2="43.18" width="0.254" layer="97"/>
<wire x1="373.38" y1="43.18" x2="354.33" y2="43.18" width="0.254" layer="97"/>
<wire x1="354.33" y1="43.18" x2="62.23" y2="43.18" width="0.254" layer="97"/>
<wire x1="62.23" y1="43.18" x2="43.18" y2="43.18" width="0.254" layer="97"/>
<wire x1="43.18" y1="43.18" x2="5.08" y2="43.18" width="0.254" layer="97"/>
<wire x1="5.08" y1="43.18" x2="5.08" y2="5.08" width="0.254" layer="97"/>
<wire x1="5.08" y1="43.18" x2="5.08" y2="871.22" width="0.254" layer="97"/>
<wire x1="1849.12" y1="871.22" x2="1849.12" y2="43.18" width="0.254" layer="97"/>
<wire x1="354.33" y1="871.22" x2="354.33" y2="43.18" width="0.254" layer="97"/>
<wire x1="373.38" y1="871.22" x2="373.38" y2="43.18" width="0.254" layer="97"/>
<wire x1="640.08" y1="871.22" x2="640.08" y2="43.18" width="0.254" layer="97"/>
<wire x1="659.13" y1="871.22" x2="659.13" y2="43.18" width="0.254" layer="97"/>
<wire x1="995.68" y1="871.22" x2="995.68" y2="43.18" width="0.254" layer="97"/>
<wire x1="1014.73" y1="871.22" x2="1014.73" y2="43.18" width="0.254" layer="97"/>
<wire x1="1376.68" y1="871.22" x2="1376.68" y2="43.18" width="0.254" layer="97"/>
<wire x1="1402.08" y1="871.22" x2="1402.08" y2="43.18" width="0.254" layer="97"/>
<text x="381" y="476.25" size="25.4" layer="97">b</text>
<text x="679.45" y="476.25" size="25.4" layer="97">b</text>
<text x="1035.05" y="482.6" size="25.4" layer="97">b</text>
<text x="1428.75" y="463.55" size="25.4" layer="97">b</text>
<text x="12.7" y="533.4" size="25.4" layer="97">a</text>
<text x="825.5" y="876.3" size="25.4" layer="97">a</text>
<text x="825.5" y="12.7" size="25.4" layer="97">a</text>
<text x="1816.1" y="444.5" size="25.4" layer="97">a</text>
<wire x1="43.18" y1="871.22" x2="43.18" y2="43.18" width="0.254" layer="97"/>
<wire x1="62.23" y1="871.22" x2="62.23" y2="43.18" width="0.254" layer="97"/>
<text x="69.85" y="476.25" size="25.4" layer="97">b*</text>
<wire x1="1811.02" y1="43.18" x2="1811.02" y2="871.22" width="0.254" layer="97"/>
<wire x1="1791.97" y1="43.18" x2="1791.97" y2="871.22" width="0.254" layer="97"/>
<text x="1784.35" y="438.15" size="25.4" layer="97" rot="R180">b*</text>
<circle x="1593.85" y="1085.85" radius="45.7905" width="0.254" layer="97"/>
<wire x1="1562.1" y1="1117.6" x2="1625.6" y2="1054.1" width="0.254" layer="97"/>
<wire x1="1625.6" y1="1117.6" x2="1562.1" y2="1054.1" width="0.254" layer="97"/>
<text x="1651" y="1073.15" size="25.4" layer="97">UP</text>
<wire x1="1562.1" y1="990.6" x2="1822.45" y2="990.6" width="0.254" layer="97"/>
<wire x1="1822.45" y1="990.6" x2="1778" y2="1009.65" width="0.254" layer="97"/>
<wire x1="1778" y1="1009.65" x2="1778" y2="971.55" width="0.254" layer="97"/>
<wire x1="1778" y1="971.55" x2="1822.45" y2="990.6" width="0.254" layer="97"/>
<text x="1835.15" y="977.9" size="25.4" layer="97">X</text>
<text x="889" y="-203.2" size="25.4" layer="97">*omit for lid</text>
</plain>
<instances>
</instances>
<busses>
</busses>
<nets>
</nets>
</sheet>
<sheet>
<plain>
<wire x1="0" y1="0" x2="0" y2="914.4" width="0.254" layer="97"/>
<wire x1="1854.2" y1="914.4" x2="1854.2" y2="0" width="0.254" layer="97"/>
<wire x1="0" y1="0" x2="43.18" y2="0" width="0.254" layer="97"/>
<wire x1="43.18" y1="0" x2="1811.02" y2="0" width="0.254" layer="97"/>
<wire x1="1811.02" y1="0" x2="1854.2" y2="0" width="0.254" layer="97"/>
<wire x1="0" y1="914.4" x2="43.18" y2="914.4" width="0.254" layer="97"/>
<wire x1="43.18" y1="914.4" x2="1811.02" y2="914.4" width="0.254" layer="97"/>
<wire x1="1811.02" y1="914.4" x2="1854.2" y2="914.4" width="0.254" layer="97"/>
<wire x1="12.7" y1="-50.8" x2="12.7" y2="-63.5" width="0.254" layer="97"/>
<wire x1="12.7" y1="-63.5" x2="12.7" y2="-76.2" width="0.254" layer="97"/>
<wire x1="12.7" y1="-63.5" x2="1841.5" y2="-63.5" width="0.254" layer="97"/>
<wire x1="1841.5" y1="-63.5" x2="1841.5" y2="-76.2" width="0.254" layer="97"/>
<wire x1="1841.5" y1="-50.8" x2="1841.5" y2="-63.5" width="0.254" layer="97"/>
<wire x1="1841.5" y1="-63.5" x2="1828.8" y2="-50.8" width="0.254" layer="97"/>
<wire x1="1841.5" y1="-63.5" x2="1828.8" y2="-76.2" width="0.254" layer="97"/>
<wire x1="12.7" y1="-63.5" x2="25.4" y2="-50.8" width="0.254" layer="97"/>
<wire x1="12.7" y1="-63.5" x2="25.4" y2="-76.2" width="0.254" layer="97"/>
<wire x1="-50.8" y1="0" x2="-63.5" y2="0" width="0.254" layer="97"/>
<wire x1="-63.5" y1="0" x2="-76.2" y2="0" width="0.254" layer="97"/>
<wire x1="-76.2" y1="12.7" x2="-63.5" y2="0" width="0.254" layer="97"/>
<wire x1="-63.5" y1="0" x2="-50.8" y2="12.7" width="0.254" layer="97"/>
<wire x1="-63.5" y1="0" x2="-63.5" y2="914.4" width="0.254" layer="97"/>
<wire x1="-63.5" y1="914.4" x2="-76.2" y2="914.4" width="0.254" layer="97"/>
<wire x1="-63.5" y1="914.4" x2="-76.2" y2="901.7" width="0.254" layer="97"/>
<wire x1="-63.5" y1="914.4" x2="-50.8" y2="901.7" width="0.254" layer="97"/>
<wire x1="-63.5" y1="914.4" x2="-50.8" y2="914.4" width="0.254" layer="97"/>
<wire x1="-76.2" y1="38.1" x2="-88.9" y2="38.1" width="0.254" layer="97"/>
<wire x1="-88.9" y1="38.1" x2="-101.6" y2="38.1" width="0.254" layer="97"/>
<wire x1="-101.6" y1="50.8" x2="-88.9" y2="38.1" width="0.254" layer="97"/>
<wire x1="-88.9" y1="38.1" x2="-76.2" y2="50.8" width="0.254" layer="97"/>
<wire x1="-88.9" y1="38.1" x2="-88.9" y2="876.3" width="0.254" layer="97"/>
<wire x1="-88.9" y1="876.3" x2="-101.6" y2="876.3" width="0.254" layer="97"/>
<wire x1="-88.9" y1="876.3" x2="-101.6" y2="863.6" width="0.254" layer="97"/>
<wire x1="-88.9" y1="876.3" x2="-76.2" y2="863.6" width="0.254" layer="97"/>
<wire x1="-88.9" y1="876.3" x2="-76.2" y2="876.3" width="0.254" layer="97"/>
<wire x1="50.8" y1="-76.2" x2="50.8" y2="-88.9" width="0.254" layer="97"/>
<wire x1="50.8" y1="-88.9" x2="50.8" y2="-101.6" width="0.254" layer="97"/>
<wire x1="50.8" y1="-88.9" x2="1803.4" y2="-88.9" width="0.254" layer="97"/>
<wire x1="1803.4" y1="-88.9" x2="1803.4" y2="-101.6" width="0.254" layer="97"/>
<wire x1="1803.4" y1="-76.2" x2="1803.4" y2="-88.9" width="0.254" layer="97"/>
<wire x1="1803.4" y1="-88.9" x2="1790.7" y2="-76.2" width="0.254" layer="97"/>
<wire x1="1803.4" y1="-88.9" x2="1790.7" y2="-101.6" width="0.254" layer="97"/>
<wire x1="50.8" y1="-88.9" x2="63.5" y2="-76.2" width="0.254" layer="97"/>
<wire x1="50.8" y1="-88.9" x2="63.5" y2="-101.6" width="0.254" layer="97"/>
<text x="-45.72" y="431.8" size="12.7" layer="97" rot="R90">36.00"</text>
<text x="-96.52" y="431.8" size="12.7" layer="97" rot="R90">33.00"</text>
<text x="904.24" y="-114.3" size="12.7" layer="97">69.00"</text>
<text x="904.24" y="-50.8" size="12.7" layer="97">72.00"</text>
<text x="279.4" y="990.6" size="50.8" layer="97">Supercooler XY (top below lid)</text>
<text x="13.97" y="-135.89" size="12.7" layer="97">a</text>
<wire x1="0" y1="-111.76" x2="38.1" y2="-111.76" width="0.1524" layer="97"/>
<wire x1="38.1" y1="-111.76" x2="38.1" y2="-149.86" width="0.1524" layer="97"/>
<wire x1="38.1" y1="-149.86" x2="0" y2="-149.86" width="0.1524" layer="97"/>
<wire x1="0" y1="-149.86" x2="0" y2="-111.76" width="0.1524" layer="97"/>
<text x="43.18" y="-144.78" size="12.7" layer="97">1.5x1.5" stud</text>
<wire x1="25.4" y1="-162.56" x2="38.1" y2="-162.56" width="0.1524" layer="97"/>
<wire x1="38.1" y1="-162.56" x2="38.1" y2="-187.96" width="0.1524" layer="97"/>
<wire x1="25.4" y1="-162.56" x2="25.4" y2="-193.04" width="0.1524" layer="97"/>
<wire x1="22.86" y1="-193.04" x2="27.94" y2="-193.04" width="0.1524" layer="97"/>
<wire x1="27.94" y1="-193.04" x2="33.02" y2="-190.5" width="0.1524" layer="97" curve="53.130102"/>
<wire x1="33.02" y1="-190.5" x2="38.1" y2="-187.96" width="0.1524" layer="97" curve="-53.130102"/>
<wire x1="38.1" y1="-187.96" x2="40.64" y2="-187.96" width="0.1524" layer="97"/>
<wire x1="22.86" y1="-195.58" x2="25.4" y2="-195.58" width="0.1524" layer="97"/>
<wire x1="25.4" y1="-195.58" x2="27.94" y2="-195.58" width="0.1524" layer="97"/>
<wire x1="27.94" y1="-195.58" x2="33.02" y2="-193.04" width="0.1524" layer="97" curve="53.130102"/>
<wire x1="33.02" y1="-193.04" x2="38.1" y2="-190.5" width="0.1524" layer="97" curve="-53.130102"/>
<wire x1="38.1" y1="-190.5" x2="40.64" y2="-190.5" width="0.1524" layer="97"/>
<wire x1="25.4" y1="-195.58" x2="25.4" y2="-210.82" width="0.1524" layer="97"/>
<wire x1="25.4" y1="-210.82" x2="38.1" y2="-210.82" width="0.1524" layer="97"/>
<wire x1="38.1" y1="-210.82" x2="38.1" y2="-190.5" width="0.1524" layer="97"/>
<text x="43.18" y="-182.88" size="12.7" layer="97">0.2" thick plywood</text>
<text x="472.44" y="-198.12" size="25.4" layer="97">external height=24"
internal hight=20"</text>
<text x="173.99" y="-137.16" size="12.7" layer="97">b</text>
<wire x1="170.18" y1="-111.76" x2="189.23" y2="-111.76" width="0.1524" layer="97"/>
<wire x1="189.23" y1="-111.76" x2="189.23" y2="-149.86" width="0.1524" layer="97"/>
<wire x1="189.23" y1="-149.86" x2="170.18" y2="-149.86" width="0.1524" layer="97"/>
<wire x1="170.18" y1="-149.86" x2="170.18" y2="-111.76" width="0.1524" layer="97"/>
<text x="200.66" y="-144.78" size="12.7" layer="97">0.75x1.5" stud</text>
<wire x1="5.08" y1="909.32" x2="43.18" y2="909.32" width="0.254" layer="97"/>
<wire x1="43.18" y1="909.32" x2="1811.02" y2="909.32" width="0.254" layer="97"/>
<wire x1="1811.02" y1="909.32" x2="1849.12" y2="909.32" width="0.254" layer="97"/>
<wire x1="1849.12" y1="909.32" x2="1849.12" y2="871.22" width="0.254" layer="97"/>
<wire x1="1849.12" y1="871.22" x2="1811.02" y2="871.22" width="0.254" layer="97"/>
<wire x1="1811.02" y1="871.22" x2="43.18" y2="871.22" width="0.254" layer="97"/>
<wire x1="43.18" y1="871.22" x2="5.08" y2="871.22" width="0.254" layer="97"/>
<wire x1="5.08" y1="871.22" x2="5.08" y2="909.32" width="0.254" layer="97"/>
<wire x1="5.08" y1="5.08" x2="1811.02" y2="5.08" width="0.254" layer="97"/>
<wire x1="1811.02" y1="5.08" x2="1849.12" y2="5.08" width="0.254" layer="97"/>
<wire x1="1849.12" y1="5.08" x2="1849.12" y2="43.18" width="0.254" layer="97"/>
<wire x1="1849.12" y1="43.18" x2="1811.02" y2="43.18" width="0.254" layer="97"/>
<wire x1="1811.02" y1="43.18" x2="43.18" y2="43.18" width="0.254" layer="97"/>
<wire x1="43.18" y1="43.18" x2="5.08" y2="43.18" width="0.254" layer="97"/>
<wire x1="5.08" y1="43.18" x2="5.08" y2="5.08" width="0.254" layer="97"/>
<wire x1="5.08" y1="43.18" x2="5.08" y2="871.22" width="0.254" layer="97"/>
<wire x1="1849.12" y1="871.22" x2="1849.12" y2="43.18" width="0.254" layer="97"/>
<text x="12.7" y="533.4" size="25.4" layer="97">b</text>
<text x="450.85" y="882.65" size="25.4" layer="97">b</text>
<text x="1079.5" y="19.05" size="25.4" layer="97">b</text>
<text x="1816.1" y="444.5" size="25.4" layer="97">b</text>
<wire x1="43.18" y1="871.22" x2="43.18" y2="43.18" width="0.254" layer="97"/>
<wire x1="1811.02" y1="43.18" x2="1811.02" y2="871.22" width="0.254" layer="97"/>
<circle x="1593.85" y="1085.85" radius="45.7905" width="0.254" layer="97"/>
<wire x1="1562.1" y1="1117.6" x2="1625.6" y2="1054.1" width="0.254" layer="97"/>
<wire x1="1625.6" y1="1117.6" x2="1562.1" y2="1054.1" width="0.254" layer="97"/>
<text x="1651" y="1073.15" size="25.4" layer="97">UP</text>
<wire x1="1562.1" y1="990.6" x2="1822.45" y2="990.6" width="0.254" layer="97"/>
<wire x1="1822.45" y1="990.6" x2="1778" y2="1009.65" width="0.254" layer="97"/>
<wire x1="1778" y1="1009.65" x2="1778" y2="971.55" width="0.254" layer="97"/>
<wire x1="1778" y1="971.55" x2="1822.45" y2="990.6" width="0.254" layer="97"/>
<text x="1835.15" y="977.9" size="25.4" layer="97">X</text>
<wire x1="43.18" y1="871.22" x2="43.18" y2="909.32" width="0.254" layer="97" style="longdash"/>
<wire x1="43.18" y1="43.18" x2="43.18" y2="0" width="0.254" layer="97" style="shortdash"/>
<wire x1="1811.02" y1="43.18" x2="1811.02" y2="5.08" width="0.254" layer="97" style="shortdash"/>
<wire x1="1811.02" y1="871.22" x2="1811.02" y2="909.32" width="0.254" layer="97" style="shortdash"/>
<wire x1="1811.02" y1="909.32" x2="1811.02" y2="914.4" width="0.254" layer="97" style="shortdash"/>
<wire x1="1811.02" y1="5.08" x2="1811.02" y2="0" width="0.254" layer="97" style="shortdash"/>
<wire x1="43.18" y1="909.32" x2="43.18" y2="914.4" width="0.254" layer="97" style="shortdash"/>
</plain>
<instances>
</instances>
<busses>
</busses>
<nets>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
<compatibility>
<note version="6.3" minversion="6.2.2" severity="warning">
Since Version 6.2.2 text objects can contain more than one line,
which will not be processed correctly with this version.
</note>
</compatibility>
</eagle>
