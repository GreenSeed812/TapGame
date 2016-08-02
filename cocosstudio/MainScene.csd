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
          <AbstractNodeData Name="displayMsg" ActionTag="2003115826" Tag="10" IconVisible="False" LeftMargin="593.5000" RightMargin="291.5000" TopMargin="160.5000" BottomMargin="464.5000" LabelText="Fnt Text Label" ctype="TextBMFontObjectData">
            <Size X="75.0000" Y="15.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="631.0000" Y="472.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.6573" Y="0.7375" />
            <PreSize X="0.0781" Y="0.0234" />
          </AbstractNodeData>
          <AbstractNodeData Name="MonsterNode" ActionTag="-1835426406" Tag="8" IconVisible="True" LeftMargin="485.3423" RightMargin="474.6577" TopMargin="487.8027" BottomMargin="152.1973" IsLoop="True" IsAutoPlay="True" CurrentAnimationName="Wait" ctype="ArmatureNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <AnchorPoint />
            <Position X="485.3423" Y="152.1973" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5056" Y="0.2378" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Normal" Path="monster_01.ExportJson" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="HpSlider" ActionTag="-1134919534" Tag="9" IconVisible="False" LeftMargin="356.0000" RightMargin="378.0000" TopMargin="155.0000" BottomMargin="463.0000" TouchEnable="True" PercentInfo="100" ctype="SliderObjectData">
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
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>