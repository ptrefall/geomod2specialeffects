
if(ButterflyEvaluator == nil) then
	ButterflyEvaluator = {}
end

if(GM_DERIVATION_EXPLICIT == nil) then
	GM_DERIVATION_EXPLICIT = 0
end

function ButterflyEvaluator:OnInit(curve)
	--curve:AddProperty("ResultSetDim", 0)
	--curve:AddProperty("DerivationMethod", 0)
	--curve:AddProperty("ResultSet", {0.0, 0.0, 0.0, 0.0})
	
	--curve:SetDerivationMethod( GM_DERIVATION_EXPLICIT )
end

function ButterflyEvaluator:OnEvent(curve, event)
	if(event.id == "Eval") then
		ButterflyEvaluator:OnEval(curve, event.arg0, event.arg1, event.arg2)
	end
end

--(Curve, Number, Integer, Boolean)
-- t -> is an arbitrary value between the start and end parameter of the curve, returned by getStartP() and getEndP()
-- d -> tells how many derivatives that should be computed at the point t
-- l -> tells whether the function (curve) is evaluated from the left or not. This defaults to true and is only utilized in "advanced" curves
function ButterflyEvaluator:OnEval(curve, t, d, l)
	curve:SetResultSetDim( d + 1 )
	
	local a = (math.exp( math.cos(t) ) - 2.0 * math.cos(4.0 * t) - math.pow( math.sin(t / 12.0), 5.0 ) )
	local a1 = 0
	local a2 = 0
	
	local s = curve:GetSize()
	
	local p00 = s * (math.cos(t) * a)
	local p01 = s * (math.sin(t) * a)
	local p02 = 0.0
	curve:SetResultSet({x=0.0, y=p00, z=p01, w=p02})
	
	if(curve:GetDerivationMethod() == GM_DERIVATION_EXPLICIT) then
		if( d > 0 ) then
			a1 = (-math.exp( math.cos(t) ) * math.sin(t) + 8.0 * math.sin(4.0 * t) - (5.0 / 12.0)* math.pow( math.sin(t / 12.0), 4.0 ) * math.cos(t / 12.0) )
			
			local p10 = s * (-math.sin(t) * a + math.cos(t) * a1)
			local p11 = s * ( math.cos(t) * a + math.sin(t) * a1)
			local p12 = 0.0
			curve:SetResultSet({x=1.0, y=p10, z=p11, w=p12})
		end
		
		if( d > 1 ) then
			a2 = (math.exp( math.cos(t) ) * math.sin(t) * math.sin(t) - math.exp( math.cos(t) ) * math.cos(t) + 8.0 * 4.0 * math.cos(4.0 * t) - (5.0/12.0)*( (1.0/3.0)* math.pow( math.sin(t / 12.0), 3.0 ) * math.pow( math.cos(t / 12.0), 2.0 ) - (1.0/12.0) * math.pow( math.sin(t / 12.0), 5.0 ) ))

			local p20 = s * (-math.cos(t) * a - math.sin(t) * a1 + math.cos(t) * a2)
			local p21 = s * (-math.sin(t) * a + math.cos(t) * a1 + math.sin(t) * a2)
			local p22 = 0.0
			curve:SetResultSet({x=2.0, y=p20, z=p21, w=p22})
		end
	end
end

RegisterComponent("ButterflyEvaluator")
