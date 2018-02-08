title = "DM2240 - Week 14 Scripting"
width = 1000
height = 600

-- Keyboard Inputs
moveForward 	= "W"
moveBackward 	= "S"
moveLeft 		= "A"
moveRight 		= "D"

--CPlayerInfo start position
CPlayerInfoStartPos = {0,0,50}

--WayPoints
Waypoint_A_1 = {x=10.0,y=0.0,z=50.0}
Waypoint_A_2 = {x=15.0,y=0.0,z=-50.0}
Waypoint_A_3 = {x=-15.0,y=0.0,z=0.0}


function SaveToLuaFile(outputString, overwrite)
	print("SaveToLuaFile...")
	local f;						-- the file
	if overwrite == 1 then			--wipe the contents with new data
		f = assert(io.open("Image/DM2240_HighScore.lua", "w"))
	elseif overwrite == 0 then		--append with new data
		f = assert(io.open("Image/DM2240_HighScore.lua", "a"))
	end
	--Write to the file
	f:write(outputString)
	--Close the file
	f:close()
	print("OK")
end

function CalculateDistanceSquare(x1,y1,z1,x2,y2,z2)
	local distanceSquare = (x2 - x1)*(x2-x1)+(y2-y1)*(y2-y1)+(z2-z1)*(z2-z1)
	print(distanceSquare)
	return distanceSquare
end

function GetMinMax(...)
	local minValue = -1
	local maxValue = -1
	local avgValue = 0
	local numValue =0
	
	for i,v in ipairs(arg) do
		if minValue == -1 then
			minValue =v
		elseif v < minValue then
			minValue = v
		end
	
		if maxValue == -1 then
			maxValue =v
		elseif v > maxValue then
			maxValue = v
		end
	
	avgValue = (avgValue * numValue + v)/ (numValue +1)
	numValue = numValue +1
	
	end
	
	avgValue = avgValue / numValue
	print(minValue,maxValue,avgValue,numValue)
	return minValue,maxValue,avgValue,numValue

end
