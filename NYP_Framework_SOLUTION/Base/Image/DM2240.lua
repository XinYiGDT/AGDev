title = "DM2240 - Week 14 Scripting"
width = 1000
height = 600

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