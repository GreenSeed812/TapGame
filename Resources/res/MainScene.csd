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
          <AbstractNodeData Name="MonsterNode" ActionTag="1028649609" Tag="8" IconVisible="True" LeftMargin="540.0000" RightMargin="540.0000" TopMargin="1020.0000" BottomMargin="900.0000" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <AnchorPoint />
            <Position X="540.0000" Y="900.0000" />
            <Scale ScaleX="2.5000" ScaleY="2.5000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.4688" />
            <PreSize X="0.0000" Y="0.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="normalAtk" ActionTag="1865554589" Tag="7" IconVisible="True" LeftMargin="540.0000" RightMargin="540.0000" TopMargin="920.0000" BottomMargin="1000.0000" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <AnchorPoint />
            <Position X="540.0000" Y="1000.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5000" Y="0.5208" />
            <PreSize X="0.0000" Y="0.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="UiNode" ActionTag="-1640237273" Tag="12" IconVisible="True" RightMargin="1080.0000" TopMargin="1920.0000" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="HpSlider" ActionTag="-1134919534" Tag="9" IconVisible="False" LeftMargin="275.5712" RightMargin="-844.5712" TopMargin="-1714.7421" BottomMargin="1662.7421" TouchEnable="True" PercentInfo="100" ctype="SliderObjectData">
                <Size X="569.0000" Y="52.0000" />
                <Children>
                  <AbstractNodeData Name="hpNow" ActionTag="2003115826" Tag="10" IconVisible="False" LeftMargin="480.0100" RightMargin="88.9900" TopMargin="14.2782" BottomMargin="37.7218" LabelText="" ctype="TextBMFontObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="480.0100" Y="37.7218" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.8436" Y="0.7254" />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="560.0712" Y="1688.7421" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <BackGroundData Type="Normal" Path="hpSliderGray.png" Plist="" />
                <ProgressBarData Type="Normal" Path="hpSliderRed.png" Plist="" />
                <BallPressedData Type="Default" Path="Default/SliderNode_Press.png" Plist="" />
                <BallDisabledData Type="Default" Path="Default/SliderNode_Disable.png" Plist="" />
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
                <BackGroundData Type="Normal" Path="time.png" Plist="" />
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
              <AbstractNodeData Name="Map" ActionTag="-1403822722" Tag="28" IconVisible="False" LeftMargin="382.3294" RightMargin="-742.3295" TopMargin="-1870.0973" BottomMargin="1755.0973" ctype="SpriteObjectData">
                <Size X="360.0000" Y="115.0000" />
                <Children>
                  <AbstractNodeData Name="MapNow" ActionTag="1338876704" Tag="46" IconVisible="False" LeftMargin="142.0918" RightMargin="131.9082" TopMargin="11.6459" BottomMargin="16.3541" ctype="SpriteObjectData">
                    <Size X="86.0000" Y="87.0000" />
                    <Children>
                      <AbstractNodeData Name="level" ActionTag="-239009431" Tag="15" IconVisible="False" LeftMargin="-4.0224" RightMargin="6.0224" TopMargin="3.5579" BottomMargin="6.4421" LabelText="111" ctype="TextBMFontObjectData">
                        <Size X="84.0000" Y="77.0000" />
                        <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                        <Position X="37.9776" Y="44.9421" />
                        <Scale ScaleX="0.9805" ScaleY="1.0041" />
                        <CColor A="255" R="253" G="255" B="254" />
                        <PrePosition X="0.4416" Y="0.5166" />
                        <PreSize X="0.9767" Y="0.8851" />
                        <LabelBMFontFile_CNB Type="Normal" Path="font.fnt" Plist="" />
                      </AbstractNodeData>
                    </Children>
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="185.0918" Y="59.8541" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5141" Y="0.5205" />
                    <PreSize X="0.2389" Y="0.7565" />
                    <FileData Type="Normal" Path="mapNow.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="MapOtherL" ActionTag="-147955816" Tag="47" IconVisible="False" LeftMargin="46.2278" RightMargin="227.7722" TopMargin="12.5160" BottomMargin="16.4840" ctype="SpriteObjectData">
                    <Size X="86.0000" Y="86.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="89.2278" Y="59.4840" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.2479" Y="0.5173" />
                    <PreSize X="0.2389" Y="0.7478" />
                    <FileData Type="Normal" Path="mapOther.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="MapOtherR" ActionTag="-1918728255" Tag="48" IconVisible="False" LeftMargin="237.0628" RightMargin="36.9372" TopMargin="11.8093" BottomMargin="17.1907" ctype="SpriteObjectData">
                    <Size X="86.0000" Y="86.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="280.0628" Y="60.1907" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.7780" Y="0.5234" />
                    <PreSize X="0.2389" Y="0.7478" />
                    <FileData Type="Normal" Path="mapOther.png" Plist="" />
                    <BlendFunc Src="1" Dst="771" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5462" ScaleY="0.8236" />
                <Position X="578.9614" Y="1849.8113" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="mapLayer.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="frame1" ActionTag="-625926874" Tag="30" IconVisible="False" LeftMargin="1.8083" RightMargin="-1071.8083" TopMargin="-1918.8491" BottomMargin="199.8491" ctype="SpriteObjectData">
                <Size X="1070.0000" Y="1719.0000" />
                <AnchorPoint ScaleX="0.5000" />
                <Position X="536.8083" Y="199.8491" />
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
                  <AbstractNodeData Name="playerButton" ActionTag="-2044542035" Tag="17" IconVisible="False" LeftMargin="-17.1521" RightMargin="766.1521" TopMargin="14.0740" BottomMargin="18.9260" TouchEnable="True" FontSize="48" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="298" Scale9Height="140" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="328.0000" Y="162.0000" />
                    <AnchorPoint ScaleX="0.3700" ScaleY="0.4717" />
                    <Position X="104.2079" Y="95.3414" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.0968" Y="0.4889" />
                    <PreSize X="0.3045" Y="0.8308" />
                    <FontResource Type="Normal" Path="font.ttf" Plist="" />
                    <TextColor A="255" R="69" G="246" B="74" />
                    <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                    <PressedFileData Type="Normal" Path="OptionButton.png" Plist="" />
                    <NormalFileData Type="Normal" Path="OptionButton.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="artifactButton" ActionTag="-219222173" Tag="19" IconVisible="False" LeftMargin="491.7288" RightMargin="257.2712" TopMargin="15.9650" BottomMargin="17.0350" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="298" Scale9Height="140" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="328.0000" Y="162.0000" />
                    <AnchorPoint ScaleX="0.4466" ScaleY="0.5000" />
                    <Position X="638.2136" Y="98.0350" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5926" Y="0.5027" />
                    <PreSize X="0.3045" Y="0.8308" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                    <PressedFileData Type="Normal" Path="OptionButton.png" Plist="" />
                    <NormalFileData Type="Normal" Path="OptionButton.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="itemButton" ActionTag="-1372702208" Tag="20" IconVisible="False" LeftMargin="743.7717" RightMargin="5.2283" TopMargin="17.7116" BottomMargin="15.2884" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="298" Scale9Height="140" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="328.0000" Y="162.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="907.7717" Y="96.2884" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.8429" Y="0.4938" />
                    <PreSize X="0.3045" Y="0.8308" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                    <PressedFileData Type="Normal" Path="OptionButton.png" Plist="" />
                    <NormalFileData Type="Normal" Path="OptionButton.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="servantButton" ActionTag="-1531893893" Tag="18" IconVisible="False" LeftMargin="239.6128" RightMargin="509.3872" TopMargin="14.6704" BottomMargin="18.3296" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="298" Scale9Height="140" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="328.0000" Y="162.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="403.6128" Y="99.3296" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.3748" Y="0.5094" />
                    <PreSize X="0.3045" Y="0.8308" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                    <PressedFileData Type="Normal" Path="OptionButton.png" Plist="" />
                    <NormalFileData Type="Normal" Path="OptionButton.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="optionframe1" ActionTag="1438620960" Tag="45" IconVisible="False" LeftMargin="-7.4388" RightMargin="-2.5613" TopMargin="3.6642" BottomMargin="134.3358" LeftEage="358" RightEage="358" TopEage="18" BottomEage="18" Scale9OriginX="358" Scale9OriginY="18" Scale9Width="371" Scale9Height="21" ctype="ImageViewObjectData">
                    <Size X="1087.0000" Y="57.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="536.0612" Y="162.8358" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.4977" Y="0.8351" />
                    <PreSize X="1.0093" Y="0.2923" />
                    <FileData Type="Normal" Path="optionFrame.png" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="optionframe2" ActionTag="-295707189" Tag="46" IconVisible="False" LeftMargin="-9.3535" RightMargin="-0.6465" TopMargin="138.4132" BottomMargin="-0.4132" FlipY="True" LeftEage="358" RightEage="358" TopEage="18" BottomEage="18" Scale9OriginX="358" Scale9OriginY="18" Scale9Width="371" Scale9Height="21" ctype="ImageViewObjectData">
                    <Size X="1087.0000" Y="57.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="534.1465" Y="28.0868" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.4960" Y="0.1440" />
                    <PreSize X="1.0093" Y="0.2923" />
                    <FileData Type="Normal" Path="optionFrame.png" Plist="" />
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
                  <AbstractNodeData Name="SkillButton1" ActionTag="-93720633" Tag="39" IconVisible="False" LeftMargin="30.6492" RightMargin="795.3508" TopMargin="251.9481" BottomMargin="28.0519" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="145" Scale9Height="154" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="175.0000" Y="176.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="118.1492" Y="116.0519" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.1180" Y="0.2545" />
                    <PreSize X="0.1748" Y="0.3860" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                    <PressedFileData Type="Normal" Path="SkillButton.png" Plist="" />
                    <NormalFileData Type="Normal" Path="SkillButton.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="SkillButton2" ActionTag="-619866290" Tag="40" IconVisible="False" LeftMargin="179.4867" RightMargin="646.5133" TopMargin="247.0387" BottomMargin="32.9613" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="145" Scale9Height="154" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="175.0000" Y="176.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="266.9867" Y="120.9613" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.2667" Y="0.2653" />
                    <PreSize X="0.1748" Y="0.3860" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                    <PressedFileData Type="Normal" Path="SkillButton.png" Plist="" />
                    <NormalFileData Type="Normal" Path="SkillButton.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="SkillButton3" ActionTag="-737616439" Tag="41" IconVisible="False" LeftMargin="333.7633" RightMargin="492.2367" TopMargin="246.2695" BottomMargin="33.7305" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="145" Scale9Height="154" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="175.0000" Y="176.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="421.2633" Y="121.7305" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.4208" Y="0.2670" />
                    <PreSize X="0.1748" Y="0.3860" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                    <PressedFileData Type="Normal" Path="SkillButton.png" Plist="" />
                    <NormalFileData Type="Normal" Path="SkillButton.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="SkillButton4" ActionTag="236016929" Tag="42" IconVisible="False" LeftMargin="488.3130" RightMargin="337.6870" TopMargin="247.1052" BottomMargin="32.8948" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="145" Scale9Height="154" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="175.0000" Y="176.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="575.8130" Y="120.8948" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5752" Y="0.2651" />
                    <PreSize X="0.1748" Y="0.3860" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                    <PressedFileData Type="Normal" Path="SkillButton.png" Plist="" />
                    <NormalFileData Type="Normal" Path="SkillButton.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="SkillButton5" ActionTag="896542495" Tag="43" IconVisible="False" LeftMargin="642.7212" RightMargin="183.2788" TopMargin="244.8588" BottomMargin="35.1412" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="145" Scale9Height="154" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="175.0000" Y="176.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="730.2212" Y="123.1412" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.7295" Y="0.2700" />
                    <PreSize X="0.1748" Y="0.3860" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                    <PressedFileData Type="Normal" Path="SkillButton.png" Plist="" />
                    <NormalFileData Type="Normal" Path="SkillButton.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="SkillButton6" ActionTag="-380060138" Tag="44" IconVisible="False" LeftMargin="797.3290" RightMargin="28.6710" TopMargin="243.1920" BottomMargin="36.8080" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="145" Scale9Height="154" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="175.0000" Y="176.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="884.8290" Y="124.8080" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.8839" Y="0.2737" />
                    <PreSize X="0.1748" Y="0.3860" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                    <PressedFileData Type="Normal" Path="SkillButton.png" Plist="" />
                    <NormalFileData Type="Normal" Path="SkillButton.png" Plist="" />
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
              <AbstractNodeData Name="Wave_Button" ActionTag="-708098858" Tag="42" IconVisible="True" LeftMargin="867.5274" RightMargin="-867.5274" TopMargin="-1816.7861" BottomMargin="1816.7861" ctype="SingleNodeObjectData">
                <Size X="0.0000" Y="0.0000" />
                <Children>
                  <AbstractNodeData Name="escapeBoss" ActionTag="1369010034" Tag="52" IconVisible="True" LeftMargin="1.5828" RightMargin="-1.5828" TopMargin="1.3514" BottomMargin="-1.3514" ctype="SingleNodeObjectData">
                    <Size X="0.0000" Y="0.0000" />
                    <AnchorPoint />
                    <Position X="1.5828" Y="-1.3514" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="WaveNum" ActionTag="-438990886" Tag="109" IconVisible="False" LeftMargin="-61.6267" RightMargin="-63.3733" TopMargin="-37.5114" BottomMargin="-39.4886" LabelText="1/10" ctype="TextBMFontObjectData">
                    <Size X="125.0000" Y="77.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="0.8733" Y="-0.9886" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="249" G="208" B="164" />
                    <PrePosition />
                    <PreSize X="0.0000" Y="0.0000" />
                    <LabelBMFontFile_CNB Type="Normal" Path="font.fnt" Plist="" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint />
                <Position X="867.5274" Y="1816.7861" />
                <Scale ScaleX="1.0000" ScaleY="1.1668" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="achiveButton" ActionTag="1617616136" Tag="49" IconVisible="False" LeftMargin="897.1228" RightMargin="-998.1228" TopMargin="-1719.9729" BottomMargin="1618.9729" TouchEnable="True" FontSize="14" ButtonText="Button" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="71" Scale9Height="79" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="101.0000" Y="101.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="947.6228" Y="1669.4729" />
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
          <AbstractNodeData Name="goldNum" ActionTag="2061361315" Tag="41" IconVisible="False" LeftMargin="527.5100" RightMargin="341.4900" TopMargin="278.6241" BottomMargin="1564.3759" LabelText="111.1aa" ctype="TextBMFontObjectData">
            <Size X="211.0000" Y="77.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="633.0100" Y="1602.8759" />
            <Scale ScaleX="0.7931" ScaleY="0.8817" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5861" Y="0.8348" />
            <PreSize X="0.1954" Y="0.0401" />
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
          <AbstractNodeData Name="BitmapFontLabel_1" ActionTag="764256369" Tag="106" IconVisible="False" LeftMargin="650.9752" RightMargin="218.0248" TopMargin="184.8856" BottomMargin="1658.1144" LabelText="111.1aa" ctype="TextBMFontObjectData">
            <Size X="211.0000" Y="77.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="756.4752" Y="1696.6144" />
            <Scale ScaleX="0.4786" ScaleY="0.3859" />
            <CColor A="255" R="251" G="208" B="165" />
            <PrePosition X="0.7004" Y="0.8837" />
            <PreSize X="0.1954" Y="0.0401" />
            <LabelBMFontFile_CNB Type="Normal" Path="font.fnt" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="Image_3" ActionTag="-1966853615" Tag="110" IconVisible="False" LeftMargin="793.7230" RightMargin="174.2770" TopMargin="101.3896" BottomMargin="1638.6104" LeftEage="36" RightEage="36" TopEage="59" BottomEage="59" Scale9OriginX="36" Scale9OriginY="59" Scale9Width="40" Scale9Height="62" ctype="ImageViewObjectData">
            <Size X="112.0000" Y="180.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="849.7230" Y="1728.6104" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.7868" Y="0.9003" />
            <PreSize X="0.1037" Y="0.0938" />
            <FileData Type="Normal" Path="yinlong.png" Plist="" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>