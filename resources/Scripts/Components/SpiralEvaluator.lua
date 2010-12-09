
if(SpiralEvaluator == nil) then
	SpiralEvaluator = {}
end

function SpiralEvaluator:OnInit(curve)
	--curve:AddProperty("ResultSetDim", 0)
	--curve:AddProperty("DerivationMethod", 0)
	--curve:AddProperty("ResultSet", {0.0, 0.0, 0.0, 0.0})
	
	--curve:SetDerivationMethod( GM_DERIVATION_EXPLICIT )
end

function SpiralEvaluator:OnEvent(curve, event)
	if(event.id = "Eval") then
		SpiralEvaluator:OnEval(curve, event.arg0, event.arg1, event.arg2)
	end
end

--(Curve, Number, Integer, Boolean)
-- t -> is an arbitrary value between the start and end parameter of the curve, returned by getStartP() and getEndP()
-- d -> tells how many derivatives that should be computed at the point t
-- l -> tells whether the function (curve) is evaluated from the left or not. This defaults to true and is only utilized in "advanced" curves
function SpiralEvaluator:OnEval(curve, t, d, l)
	curve:SetResultSetDim( d + 1 )
	
	local p00 = (4.0 * (1.0 - t) + 1.0 * t) * sin(3.0 * 6.2832 * t)
	local p01 = (4.0 * (1.0 - t) + 1.0 * t) * cos(3.0 * 6.2832 * t)
	local p02 = 5.0 * t
	curve:SetResultSet({0.0, p00, p01, p02})
	
	if(curve:GetDerivationMethod() == GM_DERIVATION_EXPLICIT) then
		if( d > 0 ) then
			local p10 =  18.8496 * ( t + 4.0 * (1.0 - t) ) * cos( 18.8496 * t ) - 3.0 * sin( 18.8496 * t )
			local p11 = -18.8496 * ( t + 4.0 * (1.0 - t) ) * sin( 18.8496 * t ) - 3.0 * cos( 18.8496 * t )
			local p12 = 5.0
			curve:SetResultSet({1.0, p10, p11, p12})
		end
	end
end

RegisterComponent("SpiralEvaluator")
