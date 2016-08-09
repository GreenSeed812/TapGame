<GameFile>
  <PropertyGroup Name="MainScene" Type="Scene" ID="a2ee0952-26b5-49ae-8bf9-4f1d6279b798" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Scene" ctype="GameNodeObjectData">
        <Size X="1080.0000" Y="1920.0000" />
        <Children>
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
                <AnchorPoint ScaleX="0.4823" ScaleY="0.5455" />
                <Position X="549.9999" Y="1691.1080" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <BackGroundData Type="Normal" Path="hpSliderGray.png" Plist="" />
                <ProgressBarData Type="Normal" Path="hpSliderRed.png" Plist="" />
                <BallPressedData Type="Default" Path="Default/SliderNode_Press.png" Plist="" />
                <BallDisabledData Type="Default" Path="Default/SliderNode_Disable.png" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Setting" ActionTag="175390128" Tag="14" IconVisible="False" LeftMargin="87.8951" RightMargin="-188.8951" TopMargin="-1859.0623" BottomMargin="1758.0623" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="71" Scale9Height="79" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="101.0000" Y="101.0000" />
                <AnchorPoint ScaleX="0.5357" ScaleY="0.3716" />
                <Position X="141.9983" Y="1795.5951" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                <NormalFileData Type="Normal" Path="setting.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="BossButton" ActionTag="-1530272840" Tag="15" IconVisible="False" LeftMargin="894.7476" RightMargin="-986.7476" TopMargin="-1767.8595" BottomMargin="1665.8595" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="62" Scale9Height="80" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="92.0000" Y="102.0000" />
                <AnchorPoint ScaleX="0.3936" ScaleY="0.4080" />
                <Position X="930.9622" Y="1707.4774" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                <NormalFileData Type="Normal" Path="bossButton.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="Mission" ActionTag="56530536" Tag="16" IconVisible="False" LeftMargin="895.5867" RightMargin="-996.5867" TopMargin="-1499.6812" BottomMargin="1398.6812" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="71" Scale9Height="79" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="101.0000" Y="101.0000" />
                <AnchorPoint ScaleX="0.2817" ScaleY="0.5310" />
                <Position X="924.0345" Y="1452.3110" />
                <Scale ScaleX="1.0044" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
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
                <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                <NormalFileData Type="Normal" Path="sign.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="timeSlider" ActionTag="1772326053" Tag="25" IconVisible="False" LeftMargin="274.3615" RightMargin="-843.3615" TopMargin="-1676.5425" BottomMargin="1624.5425" TouchEnable="True" PercentInfo="100" DisplayState="False" ctype="SliderObjectData">
                <Size X="569.0000" Y="52.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="558.8615" Y="1650.5425" />
                <Scale ScaleX="0.9708" ScaleY="0.2818" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <ProgressBarData Type="Normal" Path="time.png" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="gold" ActionTag="1418775638" Tag="27" IconVisible="False" LeftMargin="611.9484" RightMargin="-672.9484" TopMargin="-1617.7850" BottomMargin="1551.7850" LeftEage="20" RightEage="20" TopEage="21" BottomEage="21" Scale9OriginX="20" Scale9OriginY="21" Scale9Width="21" Scale9Height="24" ctype="ImageViewObjectData">
                <Size X="61.0000" Y="66.0000" />
                <AnchorPoint ScaleX="0.4500" ScaleY="0.3382" />
                <Position X="639.3969" Y="1574.1047" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="gold.png" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Map" ActionTag="-1403822722" Tag="28" IconVisible="False" LeftMargin="382.3181" RightMargin="-742.3181" TopMargin="-1870.0986" BottomMargin="1755.0986" ctype="SpriteObjectData">
                <Size X="360.0000" Y="115.0000" />
                <AnchorPoint ScaleX="0.5462" ScaleY="0.8236" />
                <Position X="578.9614" Y="1849.8113" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="mapLayer.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="frame1" ActionTag="-625926874" Tag="30" IconVisible="False" LeftMargin="8.0699" RightMargin="-1078.0698" TopMargin="-1917.8831" BottomMargin="198.8831" ctype="SpriteObjectData">
                <Size X="1070.0000" Y="1719.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="543.0699" Y="1058.3831" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="frame.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="OptionLayer" ActionTag="502162805" Tag="31" IconVisible="False" LeftMargin="2.2332" RightMargin="-1079.2332" TopMargin="-196.5800" BottomMargin="1.5800" ctype="SpriteObjectData">
                <Size X="1077.0000" Y="195.0000" />
                <Children>
                  <AbstractNodeData Name="playerButton" ActionTag="-2044542035" Tag="17" IconVisible="False" LeftMargin="-15.5709" RightMargin="764.5709" TopMargin="16.9519" BottomMargin="16.0481" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="298" Scale9Height="140" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="328.0000" Y="162.0000" />
                    <AnchorPoint ScaleX="0.3727" ScaleY="0.4717" />
                    <Position X="106.6583" Y="92.4664" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.0990" Y="0.4742" />
                    <PreSize X="0.3045" Y="0.8308" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                    <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                    <NormalFileData Type="Normal" Path="OptionButton.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="artifactButton" ActionTag="-219222173" Tag="19" IconVisible="False" LeftMargin="491.7137" RightMargin="257.2863" TopMargin="15.9651" BottomMargin="17.0349" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="298" Scale9Height="140" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="328.0000" Y="162.0000" />
                    <AnchorPoint ScaleX="0.4466" ScaleY="0.5000" />
                    <Position X="638.2136" Y="98.0350" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5926" Y="0.5027" />
                    <PreSize X="0.3045" Y="0.8308" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                    <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                    <NormalFileData Type="Normal" Path="OptionButton.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="itemButton" ActionTag="-1372702208" Tag="20" IconVisible="False" LeftMargin="743.7849" RightMargin="5.2151" TopMargin="17.7104" BottomMargin="15.2896" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="298" Scale9Height="140" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="328.0000" Y="162.0000" />
                    <AnchorPoint ScaleX="0.4463" ScaleY="0.3693" />
                    <Position X="890.1581" Y="75.1150" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.8265" Y="0.3852" />
                    <PreSize X="0.3045" Y="0.8308" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                    <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                    <NormalFileData Type="Normal" Path="OptionButton.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="servantButton" ActionTag="-1531893893" Tag="18" IconVisible="False" LeftMargin="239.6177" RightMargin="509.3823" TopMargin="14.6665" BottomMargin="18.3335" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="298" Scale9Height="140" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="328.0000" Y="162.0000" />
                    <AnchorPoint ScaleX="0.4349" ScaleY="0.3367" />
                    <Position X="382.2627" Y="72.8750" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.3549" Y="0.3737" />
                    <PreSize X="0.3045" Y="0.8308" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                    <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                    <NormalFileData Type="Normal" Path="OptionButton.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="optionframe1" ActionTag="1438620960" Tag="45" IconVisible="False" LeftMargin="-4.3107" RightMargin="-5.6892" TopMargin="3.6641" BottomMargin="134.3359" LeftEage="358" RightEage="358" TopEage="18" BottomEage="18" Scale9OriginX="358" Scale9OriginY="18" Scale9Width="371" Scale9Height="21" ctype="ImageViewObjectData">
                    <Size X="1087.0000" Y="57.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="539.1893" Y="162.8359" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5006" Y="0.8351" />
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
              <AbstractNodeData Name="SkillLayer" ActionTag="118757089" Tag="32" IconVisible="False" LeftMargin="42.0273" RightMargin="-1043.0273" TopMargin="-704.2064" BottomMargin="248.2064" LeftEage="330" RightEage="330" TopEage="150" BottomEage="150" Scale9OriginX="330" Scale9OriginY="150" Scale9Width="341" Scale9Height="156" ctype="ImageViewObjectData">
                <Size X="1001.0000" Y="456.0000" />
                <Children>
                  <AbstractNodeData Name="KeepDps" ActionTag="-865957150" Tag="35" IconVisible="False" LeftMargin="499.8965" RightMargin="105.1035" TopMargin="93.7181" BottomMargin="309.2819" LeftEage="130" RightEage="130" TopEage="17" BottomEage="17" Scale9OriginX="130" Scale9OriginY="17" Scale9Width="136" Scale9Height="19" ctype="ImageViewObjectData">
                    <Size X="396.0000" Y="53.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="697.8965" Y="335.7819" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.6972" Y="0.7364" />
                    <PreSize X="0.3956" Y="0.1162" />
                    <FileData Type="Normal" Path="keepDps .png" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="TapDps" ActionTag="-1293321369" Tag="36" IconVisible="False" LeftMargin="86.3695" RightMargin="518.6305" TopMargin="93.2336" BottomMargin="309.7664" LeftEage="130" RightEage="130" TopEage="17" BottomEage="17" Scale9OriginX="130" Scale9OriginY="17" Scale9Width="136" Scale9Height="19" ctype="ImageViewObjectData">
                    <Size X="396.0000" Y="53.0000" />
                    <AnchorPoint ScaleX="0.7233" ScaleY="0.3046" />
                    <Position X="372.7959" Y="325.9109" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.3724" Y="0.7147" />
                    <PreSize X="0.3956" Y="0.1162" />
                    <FileData Type="Normal" Path="tapDps.png" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="TotalDps" ActionTag="37583196" Tag="38" IconVisible="False" LeftMargin="90.3111" RightMargin="90.6888" TopMargin="173.9755" BottomMargin="230.0245" TouchEnable="True" ctype="SliderObjectData">
                    <Size X="820.0000" Y="52.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="500.3111" Y="256.0245" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.4998" Y="0.5615" />
                    <PreSize X="0.8192" Y="0.1140" />
                    <BackGroundData Type="Normal" Path="dpsPerS_1.png" Plist="" />
                    <ProgressBarData Type="Normal" Path="dpsPerS.png" Plist="" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="SkillButton1" ActionTag="-93720633" Tag="39" IconVisible="False" LeftMargin="16.5465" RightMargin="809.4535" TopMargin="245.8260" BottomMargin="34.1740" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="145" Scale9Height="154" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="175.0000" Y="176.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="104.0465" Y="122.1740" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.1039" Y="0.2679" />
                    <PreSize X="0.1748" Y="0.3860" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                    <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                    <NormalFileData Type="Normal" Path="SkillButton.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="SkillButton2" ActionTag="-619866290" Tag="40" IconVisible="False" LeftMargin="175.4872" RightMargin="650.5128" TopMargin="248.0387" BottomMargin="31.9613" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="145" Scale9Height="154" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="175.0000" Y="176.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="262.9872" Y="119.9613" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.2627" Y="0.2631" />
                    <PreSize X="0.1748" Y="0.3860" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                    <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                    <NormalFileData Type="Normal" Path="SkillButton.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="SkillButton3" ActionTag="-737616439" Tag="41" IconVisible="False" LeftMargin="328.7643" RightMargin="497.2357" TopMargin="244.2693" BottomMargin="35.7307" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="145" Scale9Height="154" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="175.0000" Y="176.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="416.2643" Y="123.7307" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.4158" Y="0.2713" />
                    <PreSize X="0.1748" Y="0.3860" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                    <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                    <NormalFileData Type="Normal" Path="SkillButton.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="SkillButton4" ActionTag="236016929" Tag="42" IconVisible="False" LeftMargin="485.3265" RightMargin="340.6735" TopMargin="240.0998" BottomMargin="39.9002" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="145" Scale9Height="154" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="175.0000" Y="176.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="572.8265" Y="127.9002" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.5723" Y="0.2805" />
                    <PreSize X="0.1748" Y="0.3860" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                    <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                    <NormalFileData Type="Normal" Path="SkillButton.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="SkillButton5" ActionTag="896542495" Tag="43" IconVisible="False" LeftMargin="638.7238" RightMargin="187.2762" TopMargin="240.8626" BottomMargin="39.1374" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="145" Scale9Height="154" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="175.0000" Y="176.0000" />
                    <AnchorPoint ScaleX="0.2371" ScaleY="-0.3791" />
                    <Position X="680.2140" Y="-27.5803" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.6795" Y="-0.0605" />
                    <PreSize X="0.1748" Y="0.3860" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                    <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                    <NormalFileData Type="Normal" Path="SkillButton.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                  <AbstractNodeData Name="SkillButton6" ActionTag="-380060138" Tag="44" IconVisible="False" LeftMargin="792.3314" RightMargin="33.6686" TopMargin="240.1915" BottomMargin="39.8085" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="145" Scale9Height="154" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                    <Size X="175.0000" Y="176.0000" />
                    <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                    <Position X="879.8314" Y="127.8085" />
                    <Scale ScaleX="1.0000" ScaleY="1.0000" />
                    <CColor A="255" R="255" G="255" B="255" />
                    <PrePosition X="0.8790" Y="0.2803" />
                    <PreSize X="0.1748" Y="0.3860" />
                    <TextColor A="255" R="65" G="65" B="70" />
                    <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                    <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                    <NormalFileData Type="Normal" Path="SkillButton.png" Plist="" />
                    <OutlineColor A="255" R="255" G="0" B="0" />
                    <ShadowColor A="255" R="110" G="110" B="110" />
                  </AbstractNodeData>
                </Children>
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="542.5273" Y="476.2064" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="skillLayer.png" Plist="" />
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
            <Children>
              <AbstractNodeData Name="heroDps" ActionTag="-129022496" Tag="14" IconVisible="False" LeftMargin="82.5000" RightMargin="-157.5000" TopMargin="-467.5000" BottomMargin="452.5000" LabelText="Fnt Text Label" ctype="TextBMFontObjectData">
                <Size X="75.0000" Y="15.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="120.0000" Y="460.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="0" G="0" B="0" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="herolevel" ActionTag="-2140165435" Tag="13" IconVisible="False" LeftMargin="82.5000" RightMargin="-157.5000" TopMargin="-504.5000" BottomMargin="489.5000" LabelText="Fnt Text Label" ctype="TextBMFontObjectData">
                <Size X="75.0000" Y="15.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="120.0000" Y="497.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.5333" />
                <CColor A="255" R="0" G="0" B="0" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="level" ActionTag="-239009431" Tag="15" IconVisible="False" LeftMargin="559.9716" RightMargin="-566.9716" TopMargin="-812.3791" BottomMargin="797.3791" LabelText="1" ctype="TextBMFontObjectData">
                <Size X="7.0000" Y="15.0000" />
                <AnchorPoint ScaleX="1.8063" ScaleY="0.2256" />
                <Position X="572.6157" Y="800.7624" />
                <Scale ScaleX="20.1949" ScaleY="1.4807" />
                <CColor A="255" R="0" G="0" B="0" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
              <AbstractNodeData Name="heroLevelUp" ActionTag="813120681" Tag="7" IconVisible="False" LeftMargin="295.2051" RightMargin="-341.2051" TopMargin="-995.0028" BottomMargin="959.0028" TouchEnable="True" FontSize="14" ButtonText=" 升级" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="46.0000" Y="36.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="318.2051" Y="977.0028" />
                <Scale ScaleX="2.6522" ScaleY="1.7222" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="heroLevelUP100" ActionTag="765653340" Tag="8" IconVisible="False" LeftMargin="286.9649" RightMargin="-332.9649" TopMargin="-1127.4493" BottomMargin="1091.4493" TouchEnable="True" FontSize="14" ButtonText="升100级" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="46.0000" Y="36.0000" />
                <AnchorPoint ScaleX="0.6131" />
                <Position X="315.1697" Y="1091.4493" />
                <Scale ScaleX="2.3478" ScaleY="1.6111" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <TextColor A="255" R="65" G="65" B="70" />
                <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
                <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
                <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
              <AbstractNodeData Name="hpNow" ActionTag="2003115826" Tag="10" IconVisible="False" LeftMargin="318.6242" RightMargin="-393.6242" TopMargin="-1703.4893" BottomMargin="1688.4893" LabelText="Fnt Text Label" ctype="TextBMFontObjectData">
                <Size X="75.0000" Y="15.0000" />
                <AnchorPoint ScaleX="0.4751" ScaleY="0.6843" />
                <Position X="354.2570" Y="1698.7544" />
                <Scale ScaleX="1.7461" ScaleY="1.9623" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition />
            <PreSize X="0.0000" Y="0.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>