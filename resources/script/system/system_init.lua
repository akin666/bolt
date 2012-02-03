-- Start
-- Script: script.lua
SLB.using(SLB)

-- Setup System
if System == nil then
	System = {}
	
	--
	-- Setup default paths
	-- if these get screwed, you get screwed.
	--
	System.ice_path = "ice/"
	System.resources_path = System.ice_path .. "resources/"
	System.script_path = System.resources_path .. "script/"
	System.config_path = System.resources_path .. "config/"
	System.shader_path = System.resources_path .. "shader/"
	
	System.config_default_filename = "default.cfg"
	
	System.config = Config()
	
	local default_load_success = System.config:load( System.config_path .. System.config_default_filename )
	
	if not default_load_success then
		print("Failed to load configuration file: " .. System.config_path .. System.config_default_filename )
	end
	
	-- Display setup
	System.display = DisplayManager.create( "glfw" )
	DisplayManager.set( System.display )
	System.display:setWidth( System.config:geti( "screen_width" , 800 ) )
	System.display:setHeight( System.config:geti( "screen_height" , 600 ) )
	System.display:setWindowed( System.config:getb( "screen_windowed" , true ) )
	
	if not System.display:initialize() then
		print("Display initialization failed!")
	end
	
	-- System.display:printStatistics()
	System.display:setTitle( System.config:gets( "screen_title" , "Ice, is ice cool" ) )
	
	collectgarbage("collect")
	
	-- Load common ui stuff:
	print("LOOP.lua setup UI")
	ViewportManager.create("UI")
	System.ui = {}
	System.ui.viewport = ViewportManager.get("UI")
	
	
	-- System loaded, save all default values, IF needed
	if not default_load_success then
		if not System.config:save( System.config_path .. System.config_default_filename ) then
			print("Failed to create configuration file: " .. System.config_path .. System.config_default_filename )
		end
	end
end

FontManager.load( "japan" , "ice/resources/fonts/GT2000K2.TTF" )
FontManager.load( "vera" , "ice/resources/fonts/bitstream-vera/Vera.ttf" )
FontManager.load( "rome" , "ice/resources/fonts/AGOptimaCyr_Roman.ttf" )
	
--if FontManager.hasFont( "japan" ) then
--	print("I has japan")
--end
--if FontManager.hasFont( "vera" ) then
--	print("I has vera")
--end
--if FontManager.hasFont( "rome" ) then
--	print("I has rome")
--end

-- End
