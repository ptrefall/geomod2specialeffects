
if(SpinChildEffect == nil) then
	SpinChildEffect = {}
end

function SpinChildEffect:OnInit(curve)
end

function SpinChildEffect:OnUpdate(curve, dt)
	local i = 0
	for i = 0, 56-1 do
		local local_curve = curve:GetLocalCurve(i)
		local_curve:SetRotation( {x=0.001*i+0.01*dt*i, y=0.0, z=0.0, w=1.0} )
	end
end

RegisterComponent("SpinChildEffect")
