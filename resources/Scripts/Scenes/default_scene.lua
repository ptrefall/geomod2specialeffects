
Scene = {}

function Scene:Init()
	--[[local spiral = CreateEntity("SpiralCurve")
	AddToScene(spiral)
	spiral:Replot(1000, 2)--]]
	--spiral:SetPosition({x=0.0, y=0.0, z=0.0})
	
	--local butterfly = CreateEntity("ButterflyCurve")
	--AddToScene(butterfly)
	--butterfly:Replot(1500, 2)
	--butterfly:SetPosition({x=0.0, y=0.0, z=0.0})
	
	local bezier = CreateEntity("BezierCurve")
	bezier:SetControlPoint({x=-2.0, y=0.0, z=10.0})
	bezier:SetControlPoint({x=-1.0, y=2.0, z=10.0})
	bezier:SetControlPoint({x= 1.0, y=2.0, z=10.0})
	bezier:SetControlPoint({x= 2.0, y=0.0, z=10.0})
	AddToScene(bezier)
	bezier:Replot(1000)
	
end

Scene:Init()
