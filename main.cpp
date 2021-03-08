#include <iostream>
#include <unistd.h>
#include "libraries/raytracing/raytracing.h"
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace chrono;

int main(){



  ifstream inFile;
  inFile.open("settings/settings"); //open the input file
  stringstream strStream;
  strStream << inFile.rdbuf(); //read the file
  string str = strStream.str(); //str holds the content of the file

  vector<string> lines = SplitString(str, "\n");

  float ambient_light = 0;
  int width, height, spp;
  string load_path, save_path, script_path;
  bool script_included = false;
  int startat = 0;
  int endat = -1;

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
    }else if(words[0] == "ambient-light"){
      ambient_light = stof(words[1]);
    }else if(words[0] == "script"){
      script_path = words[1];
      script_included = true;
    }else if(words[0] == "start-at"){
      startat = stoi(words[1]);
    }else if(words[0] == "end-at"){
      endat = stoi(words[1]) + 1;
    }
  }

  if(!script_included){
    cout << "Script file: ";
    cin >> script_path;
  }


  Frame frame(width, height);
  frame.spp = spp;
  frame.camera_position = Vector(0, 0, 2);
  frame.ambient_light = ambient_light;
  frame.Load(load_path);


  ifstream inFile2;
  inFile2.open(script_path); //open the input file
  stringstream strStream2;
  strStream2 << inFile2.rdbuf(); //read the file
  string script = strStream2.str(); //str holds the content of the file

  vector<string> script_lines = SplitString(script, "\n");

  int frame_num = 1;

  if(startat < 0 || startat > script_lines.size()){
    startat = 0;
  }

  if(endat < 0 || endat > script_lines.size()){
    endat = script_lines.size();
  }

  for(int i = startat; i < endat; i++){

    vector<string> command = SplitString(script_lines[i], " ");

    if(command[0] == "render"){
      cout << "Rendering frame " + to_string(frame_num) << endl;
      auto start = high_resolution_clock::now();
      frame.Render();
      frame.SaveAsPng(save_path + to_string(frame_num) + ".png");
      auto end = high_resolution_clock::now();

      cout << "Finished rendering a frame in " << duration_cast<seconds>(end - start).count() << " seconds" << endl;
      frame_num++;
    }else if(command[0] == "camera-move"){
      frame.camera_position.x = stof(command[1]);
      frame.camera_position.y = stof(command[2]);
      frame.camera_position.z = stof(command[3]);
    }else if(command[0] == "camera-direction"){
      frame.yaw = stof(command[1]);
      frame.pitch = stof(command[2]);
      frame.roll = stof(command[3]);
    }else if(command[0] == "sky-color"){
      frame.sky_red = stof(command[1]);
      frame.sky_green = stof(command[2]);
      frame.sky_blue = stof(command[3]);
    }else if(command[0] == "light-move"){
      (frame.light_sources[stoi(command[1])] -> position).x = stof(command[2]);
      (frame.light_sources[stoi(command[1])] -> position).y = stof(command[3]);
      (frame.light_sources[stoi(command[1])] -> position).z = stof(command[4]);
    }

    command = vector<string>();

  }

}
