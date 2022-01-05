# OpenGL Text Renderer

Application
    * Handles the window as a whole
    * Runs the rendering loop

Text
    * Defines a space where text can be entered
    * Defines the font which will be rendered in the space
    * Size, margins, and padding too
    * rules like how text crawling will work, will a return end the text entering, like with filenames, or simply go down a layer

Input
    * Defines each input context
    * A base class for defining buttons, checkboxes, radio buttons, etc.
    * defines which area of the window will accept glfw input

Renderer
    * Create a texture map for each font being used
    * Load textures for buttons, and other textures
    * Render the text strings for each text area

FileManager
    * Handles creating files, defines a file display area using a text area
    * Allows user to load a folder and displays all of it's subfolders

TextBuffer
    * split buffer for storing currently editing text