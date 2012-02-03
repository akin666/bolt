-- Start

--
-- if UI does not exist.. then populate the UI array AND MAKE IT EXIST!
-- 
if UI == nil then
	UI = {}	
	function UI.loadTexture( name , path )
		if not TextureManager.load( "UI" , name , path ) then
			print("Failed to load UI." .. name )
		end
	end
	
	function UI.releaseTexture( name )
		TextureManager.unload( name )
	end
end
