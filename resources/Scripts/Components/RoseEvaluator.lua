
if(RoseEvaluator == nil) then
	RoseEvaluator = {}
end

if(GM_DERIVATION_EXPLICIT == nil) then
	GM_DERIVATION_EXPLICIT = 0
end

function RoseEvaluator:OnInit(curve)
end

function RoseEvaluator:OnEvent(curve, event)
	if(event.id == "Eval") then
		RoseEvaluator:OnEval(curve, event.arg0, event.arg1, event.arg2)
	end
end

--(Curve, Number, Integer, Boolean)
-- t -> is an arbitrary value between the start and end parameter of the curve, returned by getStartP() and getEndP()
-- d -> tells how many derivatives that should be computed at the point t
-- l -> tells whether the function (curve) is evaluated from the left or not. This defaults to true and is only utilized in "advanced" curves
function RoseEvaluator:OnEval(curve, t, d, l)
	curve:SetResultSetDim( d + 1 )
	
	local r = curve:GetSize()
	local p00 = r * ( math.cos(1.75 * t) * math.cos(t))
	local p01 = r * ( math.sin(t) * math.cos(1.75 * t))
	local p02 = 0.0
	curve:SetResultSet({x=0.0, y=p00, z=p01, w=p02})
	
	if(curve:GetDerivationMethod() == GM_DERIVATION_EXPLICIT) then
		if( d > 0 ) then
			local p10 = r * ( -1.75 * math.sin( 1.75 * t ) * math.cos(t) - math.sin(t) * math.cos( 1.75 * t ) )
			local p11 = r * ( -1.75 * math.sin(t) * math.sin( 1.75 * t ) + math.cos( 1.75 * t ) * math.cos(t) )
			local p12 = 0.0
			curve:SetResultSet({x=1.0, y=p10, z=p11, w=p12})
		end
		
		if( d > 1 ) then
			local p20 = r * ( 3.5 * math.sin(t) * math.sin( 1.75 * t ) - 4.0625 * math.cos( 1.75 * t ) * math.cos(t) )
			local p21 = r * ( -3.5 * math.sin( 1.75 * t ) * math.cos(t) - 4.0625 * math.sin(t) * math.cos( 1.75 * t ) )
			local p22 = 0.0
			curve:SetResultSet({x=2.0, y=p20, z=p21, w=p22})
		end
	end
end

RegisterComponent("RoseEvaluator")
