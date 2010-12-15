
Scene = {}

function Scene:Init()
	--local spiral = CreateEntity("SpiralCurve")
	--[[AddToScene(spiral)
	spiral:Replot(1000, 2)--]]
	--spiral:SetPosition({x=0.0, y=0.0, z=0.0})
	
	--local butterfly = CreateEntity("ButterflyCurve")
	--AddToScene(butterfly)
	--butterfly:Replot(1500, 2)
	--butterfly:SetPosition({x=0.0, y=0.0, z=0.0})
	
	local rose = CreateEntity("RoseCurve")
	
	--[[local bezier = CreateEntity("BezierCurve")
	bezier:SetControlPoint({x=-1.0, y=0.0, z=0.0})
	bezier:SetControlPoint({x=0.0, y=10.0, z=0.0})
	bezier:SetControlPoint({x=10.0, y=10.0, z=0.0})
	bezier:SetControlPoint({x=10.0, y=0.0, z=0.0})
	bezier:SetControlPoint({x=20.0, y=0.0, z=0.0})
	bezier:SetControlPoint({x=20.0, y=10.0, z=0.0})
	bezier:SetControlPoint({x=-20.0, y=0.0, z=0.0})
	bezier:SetControlPoint({x=-10.0, y=0.0, z=0.0})
	bezier:SetControlPoint({x=-10.0, y=-10.0, z=0.0})
	bezier:SetControlPoint({x=0.0, y=-10.0, z=0.0})--]]
	--AddToScene(bezier)
	--bezier:Replot(100)
	
	local erbs = CreateEntity("ERBSCurve")
	erbs:SetInputCurve(rose, 56, 2, 20)
	AddToScene(erbs)
	erbs:Replot(erbs:GetReplotValue())
	
end

Scene:Init()