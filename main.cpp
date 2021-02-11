#include <iostream>
#include <unistd.h>
#include "libraries/raytracing/raytracing.h"
#include <fstream>
#include <sstream>

using namespace std;

int main(){

  ifstream inFile;
  inFile.open("settings/settings"); //open the input file
  stringstream strStream;
  strStream << inFile.rdbuf(); //read the file
  string str = strStream.str(); //str holds the content of the file

  vector<string> lines = SplitString(str, "\n");

  int width, height, spp;
  string load_path, save_path;

  for(string line : lines){
    vector<string> words = SplitString(line, " ");
    if(words[0] == "width"){
      width = stoi(words[1]);
    }else if(words[0] == "height"){
      height = stoi(words[1]);
    }else if(words[0] == "spp"){
      spp = stoi(words[1]);
    }else if(words[0] == "load"){
      load_path = words[1];
    }else if(words[0] == "save"){
      save_path = words[1];
    }
  }


  Frame frame(width, height);
  frame.spp = spp;
  frame.camera_position = Vector(0, 0, 2);
  frame.Load(load_path);


  ifstream inFile2;
  string input;
  cout << "Script file: ";
  cin >> input;
  inFile2.open(input); //open the input file
  stringstream strStream2;
  strStream2 << inFile2.rdbuf(); //read the file
  string script = strStream2.str(); //str holds the content of the file

  vector<string> script_lines = SplitString(script, "\n");

  int frame_num = 1;

  for(string sc_line : script_lines){

    vector<string> command = SplitString(sc_line, " ");

    if(command[0] == "render"){
      frame.Render();
      frame.SaveAsPng(save_path + to_string(frame_num) + ".png");
      frame_num++;
    }else if(command[0] == "camera-move"){
      frame.camera_position = Vector(stof(command[1]), stof(command[2]), stof(command[3]));
    }else if(command[0] == "camera-direction"){
      frame.yaw = stof(command[1]);
      frame.pitch = stof(command[2]);
      frame.roll = stof(command[3]);
    }else if(command[0] == "sky-color"){
      frame.sky_red = stof(command[1]);
      frame.sky_green = stof(command[2]);
      frame.sky_blue = stof(command[3]);
    }else if(command[0] == "light-move"){
      frame.light_sources[stoi(command[1])] -> position = Vector(stof(command[2]), stof(command[3]), stof(command[4]));
    }
  }

}
