
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
		--BezierEvaluator:OnEval(curve, event.arg0, event.arg1, event.arg2)
	end
end

--(Curve, Number, Integer, Boolean)
-- t -> is an arbitrary value between the start and end parameter of the curve, returned by getStartP() and getEndP()
-- d -> tells how many derivatives that should be computed at the point t
-- l -> tells whether the function (curve) is evaluated from the left or not. This defaults to true and is only utilized in "advanced" curves
function BezierEvaluator:OnEval(curve, t, d, l)
	curve:SetResultSetDim( d + 1 )
	
	--BezierEvaluator:CalcBernHermPoly(curve, t, curve:GetNumControlPoints()-1.0, curve:GetSize())
	curve:CalcBernHerm(t, curve:GetNumControlPoints()-1.0, curve:GetSize())
	
	curve:BHMultCPts()
	
	local p00 = curve:BernHermCPts(0,0)
	local p01 = curve:BernHermCPts(0,1)
	local p02 = curve:BernHermCPts(0,2)
	curve:SetResultSet({x=0.0, y=p00, z=p01, w=p02})
	
	if(curve:GetDerivationMethod() == GM_DERIVATION_EXPLICIT) then
		if(d > 0) then
			local p10 = curve:BernHermCPts(1,0)
			local p11 = curve:BernHermCPts(1,1)
			local p12 = curve:BernHermCPts(1,2)
			curve:SetResultSet({x=1.0, y=p10, z=p11, w=p12})
		end
		
		if(d > 1) then
			local p20 = curve:BernHermCPts(2,0)
			local p21 = curve:BernHermCPts(2,1)
			local p22 = curve:BernHermCPts(2,2)
			curve:SetResultSet({x=2.0, y=p20, z=p21, w=p22})
		end
		
		if(d > 2) then
			local p30 = curve:BernHermCPts(3,0)
			local p31 = curve:BernHermCPts(3,1)
			local p32 = curve:BernHermCPts(3,2)
			curve:SetResultSet({x=3.0, y=p30, z=p31, w=p32})
		end
	end
end

function BezierEvaluator:CalcBernHermPoly(curve, t, d, size)
	curve:SetBernHermDim({x=d+1, y=d+1})
	
	curve:SetBernHermMatIndex({x=d-1.0, y=0.0, z=1.0-t})
	curve:SetBernHermMatIndex({x=d-1.0, y=1.0, z=t})
	
	for i = d-2.0, 1.0, -1.0 do
		curve:SetBernHermMatIndex({x=i, y=0.0, z=((1.0-t)*curve:BernHerm(i+1.0, 0.0))})
		for j = 1, d-i, 1 do
			curve:SetBernHermMatIndex({x=i, y=j, z=(t*curve:BernHerm(i+1.0, j-1.0) + (1.0-t)*curve:BernHerm(i+1.0, j))})
		end
		curve:SetBernHermMatIndex({x=i, y=d-i, z=t*curve:BernHerm(i+1, d-i-1)})
	end
	curve:SetBernHermMatIndex({x=d, y=0.0, z=-size})
	curve:SetBernHermMatIndex({x=d, y=1.0, z=size})
	
	for k = 2, d, 1 do
		local s = k * size
		for i = d, d-k, -1 do
			curve:SetBernHermMatIndex({x=i, y=k, z=s*curve:BernHerm(i, k-1)})
			for j = k-1, 1, -1 do
				curve:SetBernHermMatIndex({x=i, y=j, z=s*(curve:BernHerm(i, j-1)-curve:BernHerm(i, j))})
			end
			curve:SetBernHermMatIndex({x=i, y=0, z=-s*curve:BernHerm(i, 0)})
		end
	end
end

RegisterComponent("BezierEvaluator")
