
Scene = {}

function Scene:Init()
	local spiral = CreateEntity("SpiralCurve")
	--AddToScene(spiral)
	--spiral:Replot(1000, 2)
	--spiral:SetPosition({x=0.0, y=0.0, z=0.0})
	
	--local butterfly = CreateEntity("ButterflyCurve")
	--AddToScene(butterfly)
	--butterfly:Replot(1500, 2)
	--butterfly:SetPosition({x=0.0, y=0.0, z=0.0})
	
	local rose = CreateEntity("RoseCurve")
	
	local bezier = CreateEntity("BezierCurve")
	bezier:SetControlPoint({x=0.0, y=0.0, z=0.0})
	bezier:SetControlPoint({x=0.0, y=0.01, z=0.0})
	bezier:SetControlPoint({x=0.0, y=2.5, z=2.5})
	bezier:SetControlPoint({x=0.5, y=5.0, z=5.0})
	bezier:SetControlPoint({x=1.0, y=10.0, z=10.0})
	--AddToScene(bezier)
	--bezier:Replot(100)
	
	local erbs = CreateEntity("ERBSCurve")
	erbs:SetInputCurve(rose, 112, 2, 500)
	AddToScene(erbs)
	erbs:Replot(erbs:GetReplotValue())
	erbs:AddComponent("SpinEffect")
	
	local erbs2 = CreateEntity("ERBSCurve")
	erbs2:SetInputCurve(rose, 112, 2, 500)
	AddToScene(erbs2)
	erbs2:Replot(erbs2:GetReplotValue())
	erbs2:SetPosition({x=0.0, y=-0.1, z=.0})
	erbs2:AddComponent("SpinEffect")
	erbs2:SetSpinDir(-1)
	
	local erbs3 = CreateEntity("ERBSCurve")
	erbs3:SetInputCurve(bezier, 56, 2, 500)
	AddToScene(erbs3)
	erbs3:Replot(erbs3:GetReplotValue())
	erbs3:SetPosition({x=0.0, y=0.1, z=0.0})
	erbs3:AddComponent("SpinEffect")
	erbs3:AddComponent("SpinChildEffect")
	
end

Scene:Init()
