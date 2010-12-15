
if(SpinEffect == nil) then
	SpinEffect = {}
end

function SpinEffect:OnInit(curve)
	curve:AddProperty("SpinAxis", {x=0.0, y=0.0, z=1.0})
	curve:AddProperty("SpinDir", 1)
end

function SpinEffect:OnUpdate(curve, dt)
	curve:SetRotation( {x=curve:GetSpinDir() * (math.sin(0.001+0.01*dt)), y=curve:GetSpinAxis().x, z=curve:GetSpinAxis().y, w=curve:GetSpinAxis().z} )
end

RegisterComponent("SpinEffect")
