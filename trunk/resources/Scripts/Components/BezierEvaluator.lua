
if(BezierEvaluator == nil) then
	BezierEvaluator = {}
end

if(GM_DERIVATION_EXPLICIT == nil) then
	GM_DERIVATION_EXPLICIT = 0
end

function BezierEvaluator:OnInit(curve)
	--curve:AddProperty("ResultSetDim", 0)
	--curve:AddProperty("DerivationMethod", 0)
	--curve:AddProperty("ResultSet", {x=0.0, y=0.0, z=0.0, w=0.0})
	--curve:AddProperty("Size", 1)
	
	--curve:SetDerivationMethod( GM_DERIVATION_EXPLICIT )
end

function BezierEvaluator:OnEvent(curve, event)
	if(event.id == "Eval") then
		BezierEvaluator:OnEval(curve, event.arg0, event.arg1, event.arg2)
	end
end

--(Curve, Number, Integer, Boolean)
-- t -> is an arbitrary value between the start and end parameter of the curve, returned by getStartP() and getEndP()
-- d -> tells how many derivatives that should be computed at the point t
-- l -> tells whether the function (curve) is evaluated from the left or not. This defaults to true and is only utilized in "advanced" curves
function BezierEvaluator:OnEval(curve, t, d, l)
	curve:SetResultSetDim( d + 1 )
	
	BezierEvaluator:CalcBernHermPoly(curve, t, curve:GetNumControlPoints()-1, curve:GetSize())
end

function BezierEvaluator:CalcBernHermPoly(curve, t, d, size)
	curve:SetBernHermDim({x=d+1, y=d+1})
	
	curve:SetBernHermMatIndex({x=d-1.0, y=0.0, z=1.0-t})
	curve:SetBernHermMatIndex({x=d-1.0, y=1.0, z=t})
	
	for i = d-2.0, i >= 0.0, i = i - 1 do
		curve:SetBernHermMatIndex({x=i, y=0.0, z=((1.0-t)*curve:GetBernHermValue(i+1, 0))})
		for j = 1, j < d-i do
			curve:SetBernHermMatIndex({x=i, y=j, z=(t*curve:GetBernHermValue(i+1, j-1) + (1-t)*curve:GetBernHermValue(i+1, j))})
		end
	end
end

RegisterComponent("BezierEvaluator")
