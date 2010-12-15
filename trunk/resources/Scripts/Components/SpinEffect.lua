
if(SpinEffect == nil) then
	SpinEffect = {}
end

function SpinEffect:OnInit(curve)
end

function SpinEffect:OnUpdate(curve, dt)
	curve:SetRotation( {x=0.1+0.01*dt, y=0.0, z=0.0, w=1.0} )
end

RegisterComponent("SpinEffect")
