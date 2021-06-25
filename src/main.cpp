/*MIT License

Copyright (c) 2021 Mohammad Issawi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/
#include<Log.h>
#include<Renderer.h>
#include<Input.h>
#include<Speaker.h>
#include<Emulator.h>
using namespace akcemu;
int main(int argc,char** args){
    std::string rom;
    int height=640;
    int width=1280;
    if(argc==4){
        height=atoi(args[1]);
        width=atoi(args[2]);
        rom=args[3];
    }else if(argc==2){
        rom=args[1];
    }else{
        LOG.error("No rom specified");
    }
    RENDERER.init(height,width);
    bool keys[16];
    SPEAKER.init();
    EMULATOR.init(700/60,rom,keys);
    INPUT.init(RENDERER.getWindow(),keys,&EMULATOR.paused);
    float startTime=glfwGetTime();
    bool wait=false;
    while(!glfwWindowShouldClose(RENDERER.getWindow())){
        if(!wait){
            EMULATOR.cycle();
            startTime=glfwGetTime();
            wait=true;
        }else if(glfwGetTime()-startTime>1.0f/60.0f){
            wait=false;
        }
    }
    RENDERER.terminate();
}