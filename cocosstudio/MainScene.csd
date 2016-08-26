<GameFile>
  <PropertyGroup Name="MainScene" Type="Scene" ID="a2ee0952-26b5-49ae-8bf9-4f1d6279b798" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Scene" ctype="GameNodeObjectData">
        <Size X="1080.0000" Y="1920.0000" />
        <Children>
          <AbstractNodeData Name="mainBG" ActionTag="1146368906" Tag="39" IconVisible="False" LeftMargin="229.1295" RightMargin="210.8705" TopMargin="258.7356" BottomMargin="921.2644" LeftEage="82" RightEage="82" TopEage="82" BottomEage="82" Scale9OriginX="82" Scale9OriginY="82" Scale9Width="476" Scale9Height="576" ctype="ImageViewObjectData">
            <Size X="640.0000" Y="740.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="549.1295" Y="1291.2644" />
            <Scale ScaleX="1.6441" ScaleY="1.6239" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5085" Y="0.6725" />
            <PreSize X="0.5926" Y="0.3854" />
            <FileData Type="Normal" Path="1.png" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="MonsterNode" ActionTag="1028649609" Tag="8" IconVisible="True" LeftMargin="544.2488" RightMargin="535.7512" TopMargin="813.7487" BottomMargin="1106.2513" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <AnchorPoint />
            <Position X="544.2488" Y="1106.2513" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5039" Y="0.5762" />
            <PreSize X="0.0000" Y="0.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="normalAtk" ActionTag="1865554589" Tag="7" IconVisible="True" LeftMargin="545.3326" RightMargin="534.6674" TopMargin="714.6851" BottomMargin="1205.3149" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <AnchorPoint />
            <Position X="545.3326" Y="1205.3149" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5049" Y="0.6278" />
            <PreSize X="0.0000" Y="0.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="UiNode" ActionTag="-1640237273" Tag="12" IconVisible="True" RightMargin="1080.0000" TopMargin="1920.0000" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="HpSlider" ActionTag="-1134919534" Tag="9" IconVisible="False" LeftMargin="279.5712" RightMargin="-840.5712" TopMargin="-1710.2421" BottomMargin="1667.2421" TouchEnable="True" PercentInfo="100" ctype="SliderObjectData">
                <Size X="561.0000" Y="43.0000" />
                <Children>
                  <AbstractNodeData Name="hpNow" ActionTag="764256369" Tag="106" IconVisible="False" LeftMargin="379.8077" RightMargin="-29.8077" TopMargin="-21.6794" BottomMargin="-12.3206" LabelText="111.1aa" ctype="TextBMFontObjectData">
                    <Size X="211.0000" Y="77.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="485.3077" Y="26.1794" />
                    <Scale ScaleX="0.4786" ScaleY="0.3859" />
                    <CColor A="255" R="251" G="208" B="165" />
                    <PrePosition X="0.8651" Y="0.6088" />
                    <PreSize X="0.3761" Y="1.7907" />
                    <LabelBMFontFile_CNB Type="Normal" Path="font.fnt" Plist="" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="560.0712" Y="1688.7421" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <BackGroundData Type="Normal" Path="kuang.png" Plist="" />
                <ProgressBarData Type="Normal" Path="hpSliderDemo.png" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Setting" ActionTag="175390128" Tag="14" IconVisible="False" LeftMargin="87.8943" RightMargin="-188.8943" TopMargin="-1859.0635" BottomMargin="1758.0635" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="71" Scale9Height="79" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="101.0000" Y="101.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="138.3943" Y="1808.5635" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Normal" Path="setting.png" Plist="" />
                <NormalFileData Type="Normal" Path="setting.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="Mission" ActionTag="56530536" Tag="16" IconVisible="False" LeftMargin="897.6488" RightMargin="-998.6488" TopMargin="-1594.4906" BottomMargin="1493.4906" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="71" Scale9Height="79" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="101.0000" Y="101.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="948.1488" Y="1543.9906" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Normal" Path="mission.png" Plist="" />
                <NormalFileData Type="Normal" Path="mission.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="SignButton" ActionTag="865362272" Tag="26" IconVisible="False" LeftMargin="89.7776" RightMargin="-190.7776" TopMargin="-1716.8545" BottomMargin="1615.8545" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="71" Scale9Height="79" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="101.0000" Y="101.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="140.2776" Y="1666.3545" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Normal" Path="sign.png" Plist="" />
                <NormalFileData Type="Normal" Path="sign.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="timeSlider" ActionTag="1772326053" Tag="25" IconVisible="False" LeftMargin="291.9375" RightMargin="-834.9375" TopMargin="-1670.7216" BottomMargin="1651.7216" TouchEnable="True" PercentInfo="100" DisplayState="False" ctype="SliderObjectData">
                <Size X="543.0000" Y="19.0000" />
                <Children>
                  <AbstractNodeData Name="Time" ActionTag="-587239375" Tag="68" IconVisible="False" LeftMargin="-37.3861" RightMargin="486.3861" TopMargin="14.0651" BottomMargin="-37.0651" FontSize="36" LabelText="30.0s" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
                    <Size X="94.0000" Y="42.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="9.6139" Y="-16.0651" />
                    <Scale ScaleX="0.5294" ScaleY="0.6477" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.0177" Y="-0.8455" />
                    <PreSize X="0.1731" Y="2.2105" />
                    <FontResource Type="Normal" Path="youyuan.ttf" Plist="" />
                    <OutlineColor A="255" R="233" G="195" B="153" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="563.4375" Y="1661.2216" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <ProgressBarData Type="Normal" Path="time.png" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="gold" ActionTag="1418775638" Tag="27" IconVisible="False" LeftMargin="467.4783" RightMargin="-528.4783" TopMargin="-1629.4989" BottomMargin="1563.4989" LeftEage="20" RightEage="20" TopEage="21" BottomEage="21" Scale9OriginX="20" Scale9OriginY="21" Scale9Width="21" Scale9Height="24" ctype="ImageViewObjectData">
                <Size X="61.0000" Y="66.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.3382" />
                <Position X="497.9783" Y="1585.8201" />
                <Scale ScaleX="1.3520" ScaleY="1.3129" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="gold.png" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Map" ActionTag="-1403822722" Tag="28" IconVisible="False" LeftMargin="345.8776" RightMargin="-742.8776" TopMargin="-1850.1080" BottomMargin="1766.1080" ctype="SpriteObjectData">
                <Size X="397.0000" Y="84.0000" />
                <Children>
                  <AbstractNodeData Name="MapNow" ActionTag="1338876704" Tag="46" IconVisible="False" LeftMargin="156.0000" RightMargin="133.0000" TopMargin="-35.3415" BottomMargin="10.3415" ctype="SpriteObjectData">
                    <Size X="108.0000" Y="109.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="210.0000" Y="64.8415" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5290" Y="0.7719" />
                    <PreSize X="0.2720" Y="1.2976" />
                    <FileData Type="Normal" Path="gongqiao (2).png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="MapOtherL" ActionTag="-147955816" Tag="47" IconVisible="False" LeftMargin="11.3200" RightMargin="300.6800" TopMargin="0.1730" BottomMargin="-1.1730" ctype="SpriteObjectData">
                    <Size X="85.0000" Y="85.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="53.8200" Y="41.3270" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.1356" Y="0.4920" />
                    <PreSize X="0.2141" Y="1.0119" />
                    <FileData Type="Normal" Path="xiaogongqiao (8).png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="MapOtherR" ActionTag="-1918728255" Tag="48" IconVisible="False" LeftMargin="302.5000" RightMargin="9.5000" TopMargin="2.1903" BottomMargin="-3.1903" ctype="SpriteObjectData">
                    <Size X="85.0000" Y="85.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="345.0000" Y="39.3097" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.8690" Y="0.4680" />
                    <PreSize X="0.2141" Y="1.0119" />
                    <FileData Type="Normal" Path="xiaogongqiao (8).png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="level" ActionTag="-239009431" Tag="15" IconVisible="False" LeftMargin="40.0300" RightMargin="330.9700" TopMargin="68.5043" BottomMargin="-61.5043" LabelText="1" ctype="TextBMFontObjectData">
                    <Size X="26.0000" Y="77.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="53.0300" Y="-23.0043" />
                    <Scale ScaleX="0.7622" ScaleY="0.7093" />
                    <CColor A="255" R="253" G="255" B="254" />
                    <PrePosition X="0.1336" Y="-0.2739" />
                    <PreSize X="0.0655" Y="0.9167" />
                    <LabelBMFontFile_CNB Type="Normal" Path="font.fnt" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="level_0" ActionTag="2043217151" Tag="1146" IconVisible="False" LeftMargin="326.0800" RightMargin="30.9200" TopMargin="68.5738" BottomMargin="-61.5738" LabelText="3" ctype="TextBMFontObjectData">
                    <Size X="40.0000" Y="77.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="346.0800" Y="-23.0738" />
                    <Scale ScaleX="0.7076" ScaleY="0.6724" />
                    <CColor A="255" R="253" G="255" B="254" />
                    <PrePosition X="0.8717" Y="-0.2747" />
                    <PreSize X="0.1008" Y="0.9167" />
                    <LabelBMFontFile_CNB Type="Normal" Path="font.fnt" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="level_1" ActionTag="1745655289" Tag="1147" IconVisible="False" LeftMargin="191.0000" RightMargin="168.0000" TopMargin="61.8626" BottomMargin="-54.8626" LabelText="2" ctype="TextBMFontObjectData">
                    <Size X="38.0000" Y="77.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="210.0000" Y="-16.3626" />
                    <Scale ScaleX="0.9805" ScaleY="1.0041" />
                    <CColor A="255" R="253" G="255" B="254" />
                    <PrePosition X="0.5290" Y="-0.1948" />
                    <PreSize X="0.0957" Y="0.9167" />
                    <LabelBMFontFile_CNB Type="Normal" Path="font.fnt" Plist="" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5462" ScaleY="0.8236" />
                <Position X="562.7190" Y="1835.2904" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="gongqiao (1).png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="frame1" ActionTag="-625926874" Tag="30" IconVisible="False" LeftMargin="1.8083" RightMargin="-1071.8083" TopMargin="-1918.8490" BottomMargin="199.8490" ctype="SpriteObjectData">
                <Size X="1070.0000" Y="1719.0000" />
                <AnchorPoint ScaleX="0.5000" />
                <Position X="536.8083" Y="199.8490" />
                <Scale ScaleX="1.0154" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="frame.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="OptionLayer" ActionTag="502162805" Tag="31" IconVisible="False" LeftMargin="2.2332" RightMargin="-1079.2332" TopMargin="-196.5800" BottomMargin="1.5800" ctype="SpriteObjectData">
                <Size X="1077.0000" Y="195.0000" />
                <Children>
                  <AbstractNodeData Name="playerButton" ActionTag="-2044542035" Tag="17" IconVisible="False" LeftMargin="41.0000" RightMargin="798.0000" TopMargin="24.6600" BottomMargin="22.3400" TouchEnable="True" FontSize="48" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="208" Scale9Height="126" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="238.0000" Y="148.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="160.0000" Y="96.3400" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.1486" Y="0.4941" />
                    <PreSize X="0.2210" Y="0.7590" />
                    <FontResource Type="Normal" Path="font.ttf" Plist="" />
                    <TextColor A="255" R="69" G="246" B="74" />
                    <DisabledFileData Type="Normal" Path="js0.png" Plist="" />
                    <PressedFileData Type="Normal" Path="js.png" Plist="" />
                    <NormalFileData Type="Normal" Path="js.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="artifactButton" ActionTag="-219222173" Tag="19" IconVisible="False" LeftMargin="539.9193" RightMargin="299.0807" TopMargin="24.6600" BottomMargin="22.3400" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="208" Scale9Height="126" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="238.0000" Y="148.0000" />
                    <AnchorPoint ScaleX="0.4466" ScaleY="0.5000" />
                    <Position X="646.2100" Y="96.3400" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.6000" Y="0.4941" />
                    <PreSize X="0.2210" Y="0.7590" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Normal" Path="sq0.png" Plist="" />
                    <PressedFileData Type="Normal" Path="sq.png" Plist="" />
                    <NormalFileData Type="Normal" Path="sq.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="itemButton" ActionTag="-1372702208" Tag="20" IconVisible="False" LeftMargin="789.7700" RightMargin="49.2300" TopMargin="24.6600" BottomMargin="22.3400" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="208" Scale9Height="126" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="238.0000" Y="148.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="908.7700" Y="96.3400" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.8438" Y="0.4941" />
                    <PreSize X="0.2210" Y="0.7590" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Normal" Path="dj0.png" Plist="" />
                    <PressedFileData Type="Normal" Path="dj0.png" Plist="" />
                    <NormalFileData Type="Normal" Path="dj.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="servantButton" ActionTag="-1531893893" Tag="18" IconVisible="False" LeftMargin="289.6100" RightMargin="549.3900" TopMargin="24.6600" BottomMargin="22.3400" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="208" Scale9Height="126" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="238.0000" Y="148.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="408.6100" Y="96.3400" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.3794" Y="0.4941" />
                    <PreSize X="0.2210" Y="0.7590" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Normal" Path="yb0.png" Plist="" />
                    <PressedFileData Type="Normal" Path="yb.png" Plist="" />
                    <NormalFileData Type="Normal" Path="yb.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="540.7332" Y="99.0800" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="optionLayer.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="SkillLayer" ActionTag="118757089" Tag="32" IconVisible="False" LeftMargin="41.0447" RightMargin="-1042.0447" TopMargin="-693.8774" BottomMargin="237.8774" LeftEage="330" RightEage="330" TopEage="150" BottomEage="150" Scale9OriginX="330" Scale9OriginY="150" Scale9Width="341" Scale9Height="156" ctype="ImageViewObjectData">
                <Size X="1001.0000" Y="456.0000" />
                <Children>
                  <AbstractNodeData Name="KeepDps" ActionTag="-865957150" Tag="35" IconVisible="False" LeftMargin="499.8965" RightMargin="105.1035" TopMargin="91.7182" BottomMargin="311.2818" LeftEage="130" RightEage="130" TopEage="17" BottomEage="17" Scale9OriginX="130" Scale9OriginY="17" Scale9Width="136" Scale9Height="19" ctype="ImageViewObjectData">
                    <Size X="396.0000" Y="53.0000" />
                    <Children>
                      <AbstractNodeData Name="KeepDps" ActionTag="-638279155" Tag="50" IconVisible="False" LeftMargin="213.3068" RightMargin="-53.3068" TopMargin="-18.5622" BottomMargin="-5.4378" LabelText="123.4aa" ctype="TextBMFontObjectData">
                        <Size X="236.0000" Y="77.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="331.3068" Y="33.0622" />
                        <Scale ScaleX="0.4048" ScaleY="0.4279" />
                        <CColor A="255" R="251" G="208" B="165" />
                        <PrePosition X="0.8366" Y="0.6238" />
                        <PreSize X="0.5960" Y="1.4528" />
                        <LabelBMFontFile_CNB Type="Normal" Path="font.fnt" Plist="" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="697.8965" Y="337.7818" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.6972" Y="0.7407" />
                    <PreSize X="0.3956" Y="0.1162" />
                    <FileData Type="Normal" Path="lv.png" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="TapDps" ActionTag="-1293321369" Tag="36" IconVisible="False" LeftMargin="86.3732" RightMargin="518.6268" TopMargin="92.2329" BottomMargin="310.7671" LeftEage="130" RightEage="130" TopEage="17" BottomEage="17" Scale9OriginX="130" Scale9OriginY="17" Scale9Width="136" Scale9Height="19" ctype="ImageViewObjectData">
                    <Size X="396.0000" Y="53.0000" />
                    <Children>
                      <AbstractNodeData Name="heroDps" ActionTag="-129022496" Tag="14" RotationSkewX="-0.0817" RotationSkewY="-0.0572" IconVisible="False" LeftMargin="223.2742" RightMargin="-45.2742" TopMargin="-18.1226" BottomMargin="-5.8774" LabelText="111.4aa" ctype="TextBMFontObjectData">
                        <Size X="218.0000" Y="77.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="332.2742" Y="32.6226" />
                        <Scale ScaleX="0.4048" ScaleY="0.4279" />
                        <CColor A="255" R="244" G="202" B="166" />
                        <PrePosition X="0.8391" Y="0.6155" />
                        <PreSize X="0.5505" Y="1.4528" />
                        <LabelBMFontFile_CNB Type="Normal" Path="font.fnt" Plist="" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.3046" />
                    <Position X="284.3732" Y="326.9109" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.2841" Y="0.7169" />
                    <PreSize X="0.3956" Y="0.1162" />
                    <FileData Type="Normal" Path="lan.png" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="TotalDps" ActionTag="37583196" Tag="38" IconVisible="False" LeftMargin="90.3112" RightMargin="90.6888" TopMargin="174.7613" BottomMargin="229.2387" TouchEnable="True" ctype="SliderObjectData">
                    <Size X="820.0000" Y="52.0000" />
                    <Children>
                      <AbstractNodeData Name="TotalDps" ActionTag="740802538" Tag="51" IconVisible="False" LeftMargin="653.3657" RightMargin="-44.3657" TopMargin="-19.5248" BottomMargin="-5.4752" LabelText="111.1aa" ctype="TextBMFontObjectData">
                        <Size X="211.0000" Y="77.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="758.8657" Y="33.0248" />
                        <Scale ScaleX="0.4048" ScaleY="0.4279" />
                        <CColor A="255" R="250" G="208" B="164" />
                        <PrePosition X="0.9254" Y="0.6351" />
                        <PreSize X="0.2573" Y="1.4808" />
                        <LabelBMFontFile_CNB Type="Normal" Path="font.fnt" Plist="" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="500.3112" Y="255.2387" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.4998" Y="0.5597" />
                    <PreSize X="0.8192" Y="0.1140" />
                    <BackGroundData Type="Normal" Path="dpsPerS_1.png" Plist="" />
                    <ProgressBarData Type="Normal" Path="dpsPerS.png" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="SkillButton1" ActionTag="-93720633" Tag="39" IconVisible="False" LeftMargin="30.6492" RightMargin="795.3508" TopMargin="252.0000" BottomMargin="28.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="145" Scale9Height="154" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="175.0000" Y="176.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="118.1492" Y="116.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.1180" Y="0.2544" />
                    <PreSize X="0.1748" Y="0.3860" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Normal" Path="zsdj-zjn.png" Plist="" />
                    <PressedFileData Type="Normal" Path="zsdj-zjn.png" Plist="" />
                    <NormalFileData Type="Normal" Path="zsdj-zjn.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="SkillButton2" ActionTag="-619866290" Tag="40" IconVisible="False" LeftMargin="175.1801" RightMargin="650.8199" TopMargin="252.0000" BottomMargin="28.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="145" Scale9Height="154" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="175.0000" Y="176.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="262.6801" Y="116.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.2624" Y="0.2544" />
                    <PreSize X="0.1748" Y="0.3860" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Normal" Path="kssj-zjm.png" Plist="" />
                    <PressedFileData Type="Normal" Path="kssj-zjm.png" Plist="" />
                    <NormalFileData Type="Normal" Path="kssj-zjm.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="SkillButton3" ActionTag="-737616439" Tag="41" IconVisible="False" LeftMargin="333.7633" RightMargin="492.2367" TopMargin="252.0000" BottomMargin="28.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="145" Scale9Height="154" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="175.0000" Y="176.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="421.2633" Y="116.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.4208" Y="0.2544" />
                    <PreSize X="0.1748" Y="0.3860" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Normal" Path="szjdj-zjm.png" Plist="" />
                    <PressedFileData Type="Normal" Path="szjdj-zjm.png" Plist="" />
                    <NormalFileData Type="Normal" Path="szjdj-zjm.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="SkillButton4" ActionTag="236016929" Tag="42" IconVisible="False" LeftMargin="486.4412" RightMargin="339.5588" TopMargin="252.0002" BottomMargin="27.9998" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="145" Scale9Height="154" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="175.0000" Y="176.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="573.9412" Y="115.9998" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5734" Y="0.2544" />
                    <PreSize X="0.1748" Y="0.3860" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Normal" Path="baofengxue-zjm.png" Plist="" />
                    <PressedFileData Type="Normal" Path="baofengxue-zjm.png" Plist="" />
                    <NormalFileData Type="Normal" Path="baofengxue-zjm.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="SkillButton5" ActionTag="896542495" Tag="43" IconVisible="False" LeftMargin="645.1566" RightMargin="180.8434" TopMargin="252.0000" BottomMargin="28.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="145" Scale9Height="154" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="175.0000" Y="176.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="732.6566" Y="116.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.7319" Y="0.2544" />
                    <PreSize X="0.1748" Y="0.3860" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Normal" Path="sx-zjm.png" Plist="" />
                    <PressedFileData Type="Normal" Path="sx-zjm.png" Plist="" />
                    <NormalFileData Type="Normal" Path="sx-zjm.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="SkillButton6" ActionTag="-380060138" Tag="44" IconVisible="False" LeftMargin="797.3290" RightMargin="28.6710" TopMargin="252.0000" BottomMargin="28.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="145" Scale9Height="154" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="175.0000" Y="176.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="884.8290" Y="116.0000" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.8839" Y="0.2544" />
                    <PreSize X="0.1748" Y="0.3860" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Normal" Path="tq-zjm.png" Plist="" />
                    <PressedFileData Type="Normal" Path="tq-zjm.png" Plist="" />
                    <NormalFileData Type="Normal" Path="tq-zjm.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="541.5447" Y="465.8774" />
                <Scale ScaleX="1.0049" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="skillLayer.png" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Wave_Button" ActionTag="-708098858" Tag="42" IconVisible="True" LeftMargin="932.8936" RightMargin="-932.8936" TopMargin="-1808.6145" BottomMargin="1808.6145" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="escapeBoss" ActionTag="1369010034" Tag="52" IconVisible="True" LeftMargin="-0.3656" RightMargin="0.3656" TopMargin="0.5768" BottomMargin="-0.5768" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="-0.3656" Y="-0.5768" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="WaveNum" ActionTag="-438990886" Tag="109" IconVisible="False" LeftMargin="-61.6251" RightMargin="-63.3749" TopMargin="-39.0595" BottomMargin="-37.9405" LabelText="1/10" ctype="TextBMFontObjectData">
                    <Size X="125.0000" Y="77.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="0.8749" Y="0.5595" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="249" G="208" B="164" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <LabelBMFontFile_CNB Type="Normal" Path="font.fnt" Plist="" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="932.8936" Y="1808.6145" />
                <Scale ScaleX="1.0000" ScaleY="1.1668" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="achiveButton" ActionTag="1617616136" Tag="49" IconVisible="False" LeftMargin="897.1200" RightMargin="-998.1200" TopMargin="-1719.9729" BottomMargin="1618.9729" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="71" Scale9Height="79" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="101.0000" Y="101.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="947.6200" Y="1669.4729" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Normal" Path="achive.png" Plist="" />
                <NormalFileData Type="Normal" Path="achive.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="optionframe2" ActionTag="-295707189" Tag="46" IconVisible="False" LeftMargin="-9.3535" RightMargin="-1077.6465" TopMargin="-56.5868" BottomMargin="-0.4132" FlipY="True" LeftEage="358" RightEage="358" TopEage="18" BottomEage="18" Scale9OriginX="358" Scale9OriginY="18" Scale9Width="371" Scale9Height="21" ctype="ImageViewObjectData">
                <Size X="1087.0000" Y="57.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="534.1465" Y="28.0868" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="optionFrame.png" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="optionframe1" ActionTag="1438620960" Tag="45" IconVisible="False" LeftMargin="-7.4388" RightMargin="-1079.5613" TopMargin="-191.3358" BottomMargin="134.3358" LeftEage="358" RightEage="358" TopEage="18" BottomEage="18" Scale9OriginX="358" Scale9OriginY="18" Scale9Width="371" Scale9Height="21" ctype="ImageViewObjectData">
                <Size X="1087.0000" Y="57.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="536.0612" Y="162.8358" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="optionFrame.png" Plist="" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="TestNode" ActionTag="478948585" Tag="13" IconVisible="True" RightMargin="1080.0000" TopMargin="1920.0000" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="goldNum" ActionTag="2061361315" Tag="41" IconVisible="False" LeftMargin="613.5100" RightMargin="427.4900" TopMargin="278.6241" BottomMargin="1564.3759" LabelText="0" ctype="TextBMFontObjectData">
            <Size X="39.0000" Y="77.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="633.0100" Y="1602.8759" />
            <Scale ScaleX="0.7931" ScaleY="0.8817" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5861" Y="0.8348" />
            <PreSize X="0.0361" Y="0.0401" />
            <LabelBMFontFile_CNB Type="Normal" Path="font.fnt" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="Sprite_14" ActionTag="826567355" Tag="104" IconVisible="False" LeftMargin="158.8847" RightMargin="870.1153" TopMargin="1409.3879" BottomMargin="484.6121" ctype="SpriteObjectData">
            <Size X="51.0000" Y="26.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="184.3847" Y="497.6121" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.1707" Y="0.2592" />
            <PreSize X="0.0472" Y="0.0135" />
            <FileData Type="Normal" Path="ms.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="dragon" ActionTag="-1966853615" VisibleForFrame="False" Tag="110" IconVisible="False" LeftMargin="793.2230" RightMargin="173.7770" TopMargin="101.3896" BottomMargin="1638.6104" LeftEage="36" RightEage="36" TopEage="59" BottomEage="59" Scale9OriginX="36" Scale9OriginY="59" Scale9Width="41" Scale9Height="62" ctype="ImageViewObjectData">
            <Size X="113.0000" Y="180.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="849.7230" Y="1728.6104" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.7868" Y="0.9003" />
            <PreSize X="0.1046" Y="0.0938" />
            <FileData Type="Normal" Path="jinlong.png" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="Warning" ActionTag="1914623536" VisibleForFrame="False" Tag="438" IconVisible="False" LeftMargin="434.9318" RightMargin="483.0682" TopMargin="1148.8101" BottomMargin="747.1899" FontSize="20" LabelText="此功能正在开发中" OutlineEnabled="True" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="TextObjectData">
            <Size X="162.0000" Y="24.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="515.9318" Y="759.1899" />
            <Scale ScaleX="2.0575" ScaleY="4.0515" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.4777" Y="0.3954" />
            <PreSize X="0.1500" Y="0.0125" />
            <FontResource Type="Normal" Path="youyuan.ttf" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>