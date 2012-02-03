-- Start
-- Script: loop.lua
print("LOOP.lua begin")

dofile( System.script_path .. "/ui/ui.lua")

UI.loadTexture( "mouse2.png" , "ice/resources/mouse/mouse2.png" )                 
UI.loadTexture( "prayer.png" , "prayer.png" )                   
UI.loadTexture( "shadowbolt.png" , "shadowbolt.png" )  
UI.loadTexture( "tausta.png" , "tausta.png" )     
UI.loadTexture( "meta.png" , "meta.png" )                        
UI.loadTexture( "button_down.png" , "button_down.png" )          
UI.loadTexture( "button_up.png" , "button_up.png" )              
UI.loadTexture( "firewall.png" , "firewall.png" )
                
print("Setup shaders")
if not ShaderManager.load( "generic.fs" , "fragment" , System.shader_path .. "generic.fs" ) then
	print("Failed to load fs")
end
if not ShaderManager.load( "generic.vs" , "vertex" , System.shader_path .. "generic.vs" ) then
	print("Failed to load vs")
end
if not ShaderManager.load( "text.fs" , "fragment" , System.shader_path .. "text.fs" ) then
	print("Failed to load fs")
end
if not ShaderManager.load( "text.vs" , "vertex" , System.shader_path .. "text.vs" ) then
	print("Failed to load vs")
end

UIProgram = ShaderProgram()
tt = ShaderManager.get("generic.fs")
UIProgram:attach( tt )
tt2 = ShaderManager.get("generic.vs")
UIProgram:attach( tt2 )

UIProgram:link()
if not UIProgram:linked() then
	print("Failed to link UIProgram")
end

TxtProgram = ShaderProgram()
tt3 = ShaderManager.get("text.fs")
TxtProgram:attach( tt3 )
tt4 = ShaderManager.get("text.vs")
TxtProgram:attach( tt4 )

print("link TxtProgram")
TxtProgram:link()
if not TxtProgram:linked() then
	print("Failed to link TxtProgram")
end

collectgarbage("collect")

print("setup UI")
-- setup UI         
frame = UIFrame() 
frame:setDimensions( System.display:getWidth() , System.display:getHeight() )
frame:initialize()
mouse = frame:getMouse()
mouse:initialize( TextureManager.getTexture( "mouse2.png" ) )
image = UIImage()
image:initialize( TextureManager.getTexture( "prayer.png" ) )
print("link TxtProgram")

collectgarbage("collect")
frame:setShader( UIProgram )

frame:getContainer():addChild( image )
UIFrameManager.setCurrent( frame )

window = UIWindow()
window:initialize( TextureManager.getTexture( "tausta.png" ) , TextureManager.getTexture( "meta.png" ) )
frame:getContainer():addChild( window )

text = UIText()
print("setshader")
text:setShader(TxtProgram)
print("got through")
text:setFont("japan")
text:setUTF8("Hello world @ABCDEFGHIJKLMN")
text:apply()
window:addChild( text )

frame:setVisible( true )

print("LOOP.lua end")                                                               
              