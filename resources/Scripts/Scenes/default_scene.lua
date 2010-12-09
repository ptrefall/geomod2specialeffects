
Scene = {}

function Scene:Init()
	local spiral = CreateEntity("SpiralCurve")
	AddToScene(spiral)
	spiral:Replot(1000, 2)
	
	local butterfly = CreateEntity("ButterflyCurve")
	AddToScene(butterfly)
	butterfly:Replot(1500, 2)
end

Scene:Init()
