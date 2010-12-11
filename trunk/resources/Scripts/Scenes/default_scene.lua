
Scene = {}

function Scene:Init()
	local spiral = CreateEntity("SpiralCurve")
	AddToScene(spiral)
	spiral:Replot(1000, 2)
	spiral:SetPosition({x=0.0, y=0.0, z=0.0})
	
	local butterfly = CreateEntity("ButterflyCurve")
	AddToScene(butterfly)
	butterfly:Replot(1500, 2)
	butterfly:SetPosition({x=-5.0, y=0.0, z=0.0})
end

Scene:Init()
