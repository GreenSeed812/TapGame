<GameFile>
  <PropertyGroup Name="MainScene" Type="Scene" ID="a2ee0952-26b5-49ae-8bf9-4f1d6279b798" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Scene" ctype="GameNodeObjectData">
        <Size X="960.0000" Y="640.0000" />
        <Children>
          <AbstractNodeData Name="Default" ActionTag="953446860" Tag="5" IconVisible="False" LeftMargin="-1.0000" RightMargin="1.0000" TopMargin="-1.0000" BottomMargin="1.0000" ctype="SpriteObjectData">
            <Size X="960.0000" Y="640.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="479.0000" Y="321.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.4990" Y="0.5016" />
            <PreSize X="1.0000" Y="1.0000" />
            <FileData Type="Normal" Path="HelloWorld.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="hpNow" ActionTag="2003115826" Tag="10" IconVisible="False" LeftMargin="690.5000" RightMargin="194.5000" TopMargin="165.5000" BottomMargin="459.5000" LabelText="Fnt Text Label" ctype="TextBMFontObjectData">
            <Size X="75.0000" Y="15.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.1000" />
            <Position X="728.0000" Y="461.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="0" B="0" />
            <PrePosition X="0.7583" Y="0.7203" />
            <PreSize X="0.0781" Y="0.0234" />
          </AbstractNodeData>
          <AbstractNodeData Name="MonsterNode" ActionTag="1028649609" Tag="8" IconVisible="True" LeftMargin="483.0000" RightMargin="477.0000" TopMargin="483.0000" BottomMargin="157.0000" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <AnchorPoint />
            <Position X="483.0000" Y="157.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5031" Y="0.2453" />
            <PreSize X="0.0000" Y="0.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="normalAtk" ActionTag="1865554589" Tag="7" IconVisible="True" LeftMargin="486.0000" RightMargin="474.0000" TopMargin="364.0000" BottomMargin="276.0000" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <AnchorPoint />
            <Position X="486.0000" Y="276.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5063" Y="0.4313" />
            <PreSize X="0.0000" Y="0.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="HpSlider" ActionTag="-1134919534" Tag="9" IconVisible="False" LeftMargin="356.0002" RightMargin="377.9998" TopMargin="155.0010" BottomMargin="462.9990" TouchEnable="True" PercentInfo="100" ctype="SliderObjectData">
            <Size X="226.0000" Y="22.0000" />
            <AnchorPoint ScaleX="0.4823" ScaleY="0.5455" />
            <Position X="465.0000" Y="475.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.4844" Y="0.7422" />
            <PreSize X="0.2354" Y="0.0344" />
            <BackGroundData Type="Normal" Path="hpSliderGray.png" Plist="" />
            <ProgressBarData Type="Normal" Path="hpSliderRed.png" Plist="" />
            <BallPressedData Type="Default" Path="Default/SliderNode_Press.png" Plist="" />
            <BallDisabledData Type="Default" Path="Default/SliderNode_Disable.png" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="heroLevelUP100" ActionTag="765653340" Tag="8" IconVisible="False" LeftMargin="96.0000" RightMargin="818.0000" TopMargin="316.0001" BottomMargin="287.9999" TouchEnable="True" FontSize="14" ButtonText="升100级" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="46.0000" Y="36.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="119.0000" Y="305.9999" />
            <Scale ScaleX="2.3478" ScaleY="1.6111" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.1240" Y="0.4781" />
            <PreSize X="0.0479" Y="0.0562" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
            <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="heroLevelUp" ActionTag="813120681" Tag="7" IconVisible="False" LeftMargin="99.0000" RightMargin="815.0000" TopMargin="218.0000" BottomMargin="386.0000" TouchEnable="True" FontSize="14" ButtonText=" 升级" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="46.0000" Y="36.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="122.0000" Y="404.0000" />
            <Scale ScaleX="2.6522" ScaleY="1.7222" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.1271" Y="0.6313" />
            <PreSize X="0.0479" Y="0.0562" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
            <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="herolevel" ActionTag="-2140165435" Tag="13" IconVisible="False" LeftMargin="82.5000" RightMargin="802.5000" TopMargin="135.5000" BottomMargin="489.5000" LabelText="Fnt Text Label" ctype="TextBMFontObjectData">
            <Size X="75.0000" Y="15.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="120.0000" Y="497.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.5333" />
            <CColor A="255" R="0" G="0" B="0" />
            <PrePosition X="0.1250" Y="0.7766" />
            <PreSize X="0.0781" Y="0.0234" />
          </AbstractNodeData>
          <AbstractNodeData Name="heroDps" ActionTag="-129022496" Tag="14" IconVisible="False" LeftMargin="82.5000" RightMargin="802.5000" TopMargin="172.5000" BottomMargin="452.5000" LabelText="Fnt Text Label" ctype="TextBMFontObjectData">
            <Size X="75.0000" Y="15.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="120.0000" Y="460.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="0" G="0" B="0" />
            <PrePosition X="0.1250" Y="0.7188" />
            <PreSize X="0.0781" Y="0.0234" />
          </AbstractNodeData>
          <AbstractNodeData Name="level" ActionTag="-239009431" Tag="15" IconVisible="False" LeftMargin="720.5000" RightMargin="232.5000" TopMargin="132.5000" BottomMargin="492.5000" LabelText="1" ctype="TextBMFontObjectData">
            <Size X="7.0000" Y="15.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="724.0000" Y="500.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="0" G="0" B="0" />
            <PrePosition X="0.7542" Y="0.7813" />
            <PreSize X="0.0073" Y="0.0234" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>