
if(SpinChildEffect == nil) then
	SpinChildEffect = {}
end

function SpinChildEffect:OnInit(curve)
end

function SpinChildEffect:OnUpdate(curve, dt)
	local num_curves = curve:GetNumLocalCurves()
	for i = 0, num_curves-1 do
		local local_curve = curve:GetLocalCurve(i)
		local_curve:SetRotation( {x=dt, y=0.0, z=0.0, w=1.0} )
	end
end

RegisterComponent("SpinChildEffect")
