# Engine3D-Sandbox
Engine3D Sandbox is used for specifically testing and experimenting with Engine3D's API calls.

## Overview
Specifically also used to demonstrate how to use the API at a very basic level for a quick starter guide, as well.

## Resources Link
Drawing a circle example here - `https://stackoverflow.com/questions/22444450/drawing-circle-with-opengl`

## Starter Guide
* To draw a square do the following 
* The format is drawQuad(pos, size, color) \
`Renderer2D::drawQuad({0.f, 0.f}, {0.5f, 0.5f}, color);`

* If you want to render a texture then do the following below
* This is also how to load in a texture and use it to draw the quad. \
`auto texture = Texture2D::Create("assets/textureFilename.png");` \
`Renderer2D::drawQuad({0.f, 0.f}, {0.5f, 0.5f}, texture);`
