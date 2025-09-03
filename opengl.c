//if windows
#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <GL/glut.h>


//GUI object
short g_pos[3*4*15] = {
0,0,0, 256,0,0, 256,800,0, 0,800,0,//GUI background
0,0,0, 256,0,0, 256,32,0, 0,32,0,//GUI title
0,64,0,256,64,0,256,320,0,0,320,0,//GUI tileset
16,328,0, 240,328,0,  240,520,0, 16,520,0,//GUI Palette
0,320,0, 256,320,0, 256,448,0, 0,448,0,//GUI info
0,0,0,  32,0,0,  32, 32,0, 0, 32,0,//GUI selected bg palette
0,0,0,  32,0,0,  32, 32,0, 0, 32,0,//GUI selected fg palette
0,0,0,  24,0,0,  24, 24,0, 0, 24,0,//GUI selected tile on tileset
//Buttons
16,24,0, 48,24,0, 48,56,0, 16,56,0,
48,24,0, 80,24,0, 80,56,0, 48,56,0,
80,24,0, 112,24,0, 112,56,0, 80,56,0,
112,24,0, 144,24,0, 144,56,0, 112,56,0,
144,24,0, 176,24,0, 176,56,0, 144,56,0,
176,24,0, 208,24,0, 208,56,0, 176,56,0,
208,24,0, 240,24,0, 240,56,0, 208,56,0,
};

float g_coord[2*4*15] = {
0,1,1,1,1,1,0,1,
0.500000,12.0/32,1,12.0/32,1,14.0/32,0.500000,14.0/32,
0,0,0.5,0,0.5,0.5,0,0.5,
16.0/32.0,0,17.0/32.0,0,17.0/32.0,1.0/32.0,16.0/32.0,1.0/32.0,
0,0.5,1,0.5,1,1,0,1,

6.0/8.0,2.0/8.0, 7.0/8.0,2.0/8.0,7.0/8.0,3.0/8.0,6.0/8.0,3.0/8.0,
7.0/8.0,2.0/8.0, 8.0/8.0,2.0/8.0,8.0/8.0,3.0/8.0,7.0/8.0,3.0/8.0,
5.0/8.0,0, 6.0/8.0,0, 6.0/8.0,1.0/8.0,5.0/8.0,1.0/8.0,

6.0/8.0,0,7.0/8.0,0,7.0/8.0,1.0/8.0,6.0/8.0,1.0/8.0,
7.0/8.0,0,8.0/8.0,0,8.0/8.0,1.0/8.0,7.0/8.0,1.0/8.0,
4.0/8.0,1.0/8.0,5.0/8.0,1.0/8.0,5.0/8.0,2.0/8.0,4.0/8.0,2.0/8.0,
5.0/8.0,1.0/8.0,6.0/8.0,1.0/8.0,6.0/8.0,2.0/8.0,5.0/8.0,2.0/8.0,
6.0/8.0,1.0/8.0,7.0/8.0,1.0/8.0,7.0/8.0,2.0/8.0,6.0/8.0,2.0/8.0,
0.5,0.25, 0.625,0.25, 0.625,0.375,0.5,0.375,
5.0/8.0,2.0/8.0,6.0/8.0,2.0/8.0,6.0/8.0,3.0/8.0,5.0/8.0,3.0/8.0,
};

extern char binary_numbers_data_start[];
extern char binary_gui0_data_start[];

//texture coords
typedef struct {
	float u;
	float v;
}TexCoord2f;

//vertex position
typedef struct {
	short x;
	short y;
	short z;
}Vertex3s;

//vertex color
typedef struct {
	unsigned char r;
	unsigned char g;
	unsigned char b;
}Color3b;

//Vertices fg
typedef struct {
	TexCoord2f *coord;
	Vertex3s *pos;
	Color3b *col;
}cell_vertex;

//Vertices bg
typedef struct {
	Vertex3s *pos;
	Color3b *col;
}cell_vertex_1;

//Vertices select
typedef struct {
	Vertex3s *pos;
}cell_vertex_2;


cell_vertex_1 bg_vertices;
cell_vertex fg_vertices;
cell_vertex_1 bg_buffer_vertices;
cell_vertex fg_buffer_vertices;
cell_vertex collision_vertices;
cell_vertex grid_vertices;
cell_vertex gui_vertices;
cell_vertex select_vertices;
cell_vertex fixed_vertices;
cell_vertex_2 select_vertices_2;

//Screen dimension constants
int SCREEN_WIDTH = 1024;
int SCREEN_HEIGHT = 600;
int SCALE = 0;
int EGA_MODE = 0;
int EDITTING_EGA_PALETTE = 0;
int EGA_selected_color_index = 0;
float M_scale[] = {0.5,0.25};
int G_scale[] = {2,4};
int running = 1;
int Grab_Map = 0;
int Get_Tile = 0;
int Get_Tile_Group = 0;
int Set_Tile = 0;
int Get_Tile_X = 0;
int Get_Tile_Y = 0;
int GTX = 0,GTY = 0;
int sizex = 0;
int sizey = 0;
int sizx = 0;
int sizy = 0;
int SCR_X = 128;
int SCR_Y = 0;
int map_x = 0;
int map_y = 0;
int map_width = 40;
int map_height = 30;
int map_w = 0; 
int map_h = 0;
int setting_width = 0;
int setting_height = 0;
int setting_digit = 0;
int setting_blink = 0;
int sx0,sy0,sx1,sy1;
int tile_X,tile_Y,palette;
int type_tile_X,type_tile_Y,start_type_tile_X,Type_ON = 0;
float movx = 0,movy = 0;
float map_scale = 0.5;
float gui_scale = 2;
int grid_state = 1;
Color3b grid_color = (Color3b){255,0,0};
Color3b sel_tile_col = (Color3b){255,0,0};
int cycle_color_state = 0;
int button_x = -48;
int mouse_x,mouse_y,mx,my;
GLuint texture_tiles;
GLuint texture_gui0;
GLuint texture_grid;
float tex_cel = 0.0625;

unsigned char buffer_tiles[128*128] = {0};
unsigned char buffer_bgcolor[128*128] = {0};
unsigned char buffer_fgcolor[128*128] = {0};
int map_palette_EGA[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
Color3b map_palette_EGA_Temp[16];
Color3b EGA_pal[16] = {
	{0x00,0x00,0x00},{0x00,0x00,0xaa},{0x00,0xaa,0x00},{0x00,0xaa,0xaa},
	{0xaa,0x00,0x00},{0xaa,0x00,0xaa},{0xaa,0x55,0x00},{0xaa,0xaa,0xaa},
	{0x55,0x55,0x55},{0x55,0x55,0xff},{0x55,0xff,0x55},{0x55,0xff,0xff},
	{0xff,0x55,0x55},{0xff,0x55,0xff},{0xff,0xff,0x55},{0xff,0xff,0xff}
};
Color3b map_palette[16] = {
	{0x00,0x00,0x00},{0x00,0x00,0xaa},{0x00,0xaa,0x00},{0x00,0xaa,0xaa},
	{0xaa,0x00,0x00},{0xaa,0x00,0xaa},{0xaa,0x55,0x00},{0xaa,0xaa,0xaa},
	{0x55,0x55,0x55},{0x55,0x55,0xff},{0x55,0xff,0x55},{0x55,0xff,0xff},
	{0xff,0x55,0x55},{0xff,0x55,0xff},{0xff,0xff,0x55},{0xff,0xff,0xff}
};
unsigned char map_char[512*512] = {0};
unsigned char map_bgcolor[512*512] = {0};
unsigned char map_fgcolor[512*512] = {0};
unsigned int *map_chunk_index;

unsigned char raw_1bitPNG_tile_bytes[8*256] = {0};
unsigned char tile_pixels[256*256*3] = {0};
unsigned char selected_tile_pixels[48*48*3] = {0};

char *filename;
OPENFILENAME ofn;       // common dialog box structure
char szFile[260];       // buffer for file name
HWND hwnd = 0;          // owner window
HANDLE hf;

CHOOSECOLOR cc;                 // common dialog box structure 
static COLORREF acrCustClr[16]; // array of custom colors 
HBRUSH hbrush;                  // brush handle
static DWORD rgbCurrent;        // initial color selection


///IO
void Open_File(int mode){
	//ofn = (OPENFILENAME*) calloc(1,sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFile = szFile;
    //
    // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
    // use the contents of szFile to initialize itself.
    //
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
	if (mode == 0) ofn.lpstrFilter = "Load Tileset PNG (1Bit)\0*.*\0PNG\0*.png\0";
    if (mode == 1) ofn.lpstrFilter = "Load EGA/VGA MAP Files\0*.*\0Map\0*.map\0";
	if (mode == 2) ofn.lpstrFilter = "Save EGA/VGA MAP Files\0*.*\0Map\0*.map\0";
	if (mode == 3) ofn.lpstrFilter = "Save EGA/VGA Tileset (1Bit)\0*.*\0Til\0*.til\0";
	if (mode == 4) ofn.lpstrFilter = "Load GIMP TXT Palette\0*.*\0Txt\0*.txt\0";
    
	ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
	
	// Display the Open dialog box. 
	if (mode < 2){
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
		if (GetOpenFileName(&ofn)==TRUE){ 
			hf = CreateFile(ofn.lpstrFile, GENERIC_READ,
				0, (LPSECURITY_ATTRIBUTES) NULL,
				OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
				(HANDLE) NULL);
			filename = ofn.lpstrFile;
			CloseHandle(hf);
		} 
	} else {
		ofn.Flags = OFN_PATHMUSTEXIST;
		GetOpenFileName(&ofn);
		hf = CreateFile(ofn.lpstrFile, GENERIC_WRITE,
			0, (LPSECURITY_ATTRIBUTES) NULL,
			CREATE_NEW, FILE_ATTRIBUTE_NORMAL,
			(HANDLE) NULL);
		filename = ofn.lpstrFile;
		CloseHandle(hf);
	}
}

void Export_EGA_VGA_Tileset(){
	Open_File(3);
	FILE *f = fopen(filename,"wb");
	if (!f) return;
	
	fwrite(raw_1bitPNG_tile_bytes,1,8*256,f);
	
	fclose(f);
}

void Load_Tileset(){
	int x,y,z,index0,index = 0;
	Open_File(0);
	FILE *f = fopen(filename,"rb");
	if (!f) return;
	// 128x128 1 bit png, each line is stored in 16 bytes + 1 extra at the end
	
	//get tiles for editor
	fseek(f, 0x43, SEEK_SET);
	for (y = 0; y < 128; y++){
		fread(&tile_pixels[index],1,16,f);
		fgetc(f);
		index+=16;
	}
	//store raw tiles in a column to export for EGA/VGA
	index = 0;index0 = 0;
	for (y = 0; y != 128; y+=8){
		for(x = 0; x != 16;x++){
			index = (y*16) + x;
			for(z = 0; z != 8;z++){
				raw_1bitPNG_tile_bytes[index0] = tile_pixels[index];
				index0++;index+=16;
			}
		}
	}

	float color_index[] = {0.0, 1.0};
	
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glPixelMapfv(GL_PIXEL_MAP_I_TO_R, 2, color_index);
	glPixelMapfv(GL_PIXEL_MAP_I_TO_G, 2, color_index);
	glPixelMapfv(GL_PIXEL_MAP_I_TO_B, 2, color_index);
	glPixelMapfv(GL_PIXEL_MAP_I_TO_A, 2, color_index);
	glBindTexture(GL_TEXTURE_2D, texture_tiles);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,128,128,0,GL_COLOR_INDEX,GL_BITMAP,tile_pixels);
	
	//Convert to rgb
	index = 0;
	fseek(f, 0x43, SEEK_SET);
	for (y = 0; y < 128; y++){
		for(x = 0; x != 16;x++){
			unsigned char pixels = fgetc(f);
			unsigned char _byte = 0x80;
			for(z = 0; z != 8;z++){
				unsigned char color;
				if (pixels & _byte) color = 255;
				else color = 0;
				tile_pixels[index++] = color;
				tile_pixels[index++] = color;
				tile_pixels[index++] = color;
				_byte >>=1;
			}
		}
		fgetc(f);
	}
	
	fclose(f);
	//Copy to gui texture
	glBindTexture(GL_TEXTURE_2D, texture_gui0);
	glTexSubImage2D(GL_TEXTURE_2D,0,0,0,128,128,GL_RGB,GL_UNSIGNED_BYTE,tile_pixels);
}

void Reset_Map(){
	//set a default 40x30 black map
	int x = 0; int y = 0; int index = 0; int skip = 0;
	Color3b color;
	for (int i = 0; i < (512*512); i++){
		skip = 0;
		if (x > map_width-1) skip = 1;
		if (y > map_height-1) skip = 1;
		if (skip == 1) color = (Color3b){30,30,30}; 
		else color = map_palette[map_bgcolor[0]];
		bg_vertices.col[index  ] = color;
		bg_vertices.col[index+1] = color;
		bg_vertices.col[index+2] = color;
		bg_vertices.col[index+3] = color;
		
		if (skip == 1) color = (Color3b){30,30,30}; 
		else color = map_palette[map_fgcolor[15]];
		fg_vertices.col[index  ] = color;
		fg_vertices.col[index+1] = color;
		fg_vertices.col[index+2] = color;
		fg_vertices.col[index+3] = color;
		
		index+=4;
		x++;
		if (x == 512) {x = 0; y++;}
	}
}

void Load_Map(int mode){
	int i,x,y;
	int index = 0, cindex = 0, row = 0;
	if (mode) Open_File(1);
	FILE *f = fopen(filename,"rb");
	if (!f) return;
	fread(&map_width,1,2,f);
	fread(&map_height,1,2,f);
	if (map_width*map_height > 512*512) return;
	Reset_Map();
	map_w = map_width;
	map_h = map_height;
	for (i = 0; i < 16; i++){
		unsigned char c = fgetc(f);
		if (c >15)c-=8;//ega default colors: 0-7  16-23
		map_palette_EGA[i] = c;
	}
	for (i = 0; i < 16; i++){
		unsigned char r = fgetc(f);//<<2;
		unsigned char g = fgetc(f);//<<2;
		unsigned char b = fgetc(f);//<<2;
		map_palette[i] = (Color3b){r,g,b};
	}
	for (y = 0; y < map_height; y++){
		for (x = 0; x < map_width; x++){
			int index = (y*512)+x;
			unsigned char c;
			map_char[index] = fgetc(f);
			c = fgetc(f);
			map_bgcolor[index] = c >> 4;
			map_fgcolor[index] = c & 0x0F; 
		}
	}
	fclose(f);
	for (y = 0; y < map_height; y++){
		for (x = 0; x < map_width; x++){
			cindex = (y*512)+x;
			index = cindex*4;
			Color3b color = map_palette[map_bgcolor[cindex]];
			bg_vertices.col[index  ] = color;
			bg_vertices.col[index+1] = color;
			bg_vertices.col[index+2] = color;
			bg_vertices.col[index+3] = color;
			
			color = map_palette[map_fgcolor[cindex]];
			fg_vertices.col[index  ] = color;
			fg_vertices.col[index+1] = color;
			fg_vertices.col[index+2] = color;
			fg_vertices.col[index+3] = color;
			
			int tilex = map_char[cindex] & 15;
			int tiley = map_char[cindex] >> 4;
			float tx = tilex*tex_cel;
			float ty = tiley*tex_cel;
			fg_vertices.coord[index  ] = (TexCoord2f) {tx,ty};
			fg_vertices.coord[index+1] = (TexCoord2f) {tx+tex_cel,ty};
			fg_vertices.coord[index+2] = (TexCoord2f) {tx+tex_cel,ty+tex_cel};
			fg_vertices.coord[index+3] = (TexCoord2f) {tx,ty+tex_cel};
		}
	}
	
	//Change palette on gui
	glBindTexture(GL_TEXTURE_2D, texture_gui0);
	glTexSubImage2D(GL_TEXTURE_2D,0,128,0,8,2,GL_RGB,GL_UNSIGNED_BYTE,map_palette);
}

void Save_Map(){
	int i,x,y;
	Open_File(2);
	FILE *f = fopen(filename,"wb");
	fwrite(&map_width,1,2,f);
	fwrite(&map_height,1,2,f);
	for (i = 0; i < 16; i++){
		unsigned char c = map_palette_EGA[i];
		if (c >7)c+=8;//ega default colors: 0-7  16-23
		fputc(c,f);
	}
	for (i = 0; i < 16; i++){
		Color3b c = map_palette[i];
		unsigned char r = c.r;//>>2;
		unsigned char g = c.g;//>>2;
		unsigned char b = c.b;//>>2;
		fwrite(&r,1,1,f);
		fwrite(&g,1,1,f);
		fwrite(&b,1,1,f);
	}
	for (y = 0; y < map_height; y++){
		for (x = 0; x < map_width; x++){
			int index = (y*512)+x;
			unsigned char a = (map_bgcolor[index] << 4) | (map_fgcolor[index] & 0x0F); 
			unsigned char c = map_char[index];
			fwrite(&c,1,1,f);
			fwrite(&a,1,1,f);
		}
	}
	fclose(f);
}

void Load_Palette(){
	int i;
	int index = 0, cindex = 0, row = 0;
	char line[128] = {0};
	Open_File(4);
	FILE *f = fopen(filename,"rb");
	if (!f) return;
	fseek(f, 0, SEEK_SET);
	for (i = 0; i < 16; i++){
		Color3b c,d;
		memset(line, 0, 128);
		fgets(line, 128, f);		
		sscanf(line, "#%06X",(unsigned int*)&c);
		d.r = c.b; 
		d.g = c.g;
		d.b = c.r;
		map_palette[i] = d;
	}
	fclose(f);
	
	//Update map and palette gui
	index = 0;
	for (i = 0; i < (map_width*map_height); i++){
		Color3b color = map_palette[map_bgcolor[cindex]];
		bg_vertices.col[index  ] = color;
		bg_vertices.col[index+1] = color;
		bg_vertices.col[index+2] = color;
		bg_vertices.col[index+3] = color;
		
		color = map_palette[map_fgcolor[cindex]];
		fg_vertices.col[index  ] = color;
		fg_vertices.col[index+1] = color;
		fg_vertices.col[index+2] = color;
		fg_vertices.col[index+3] = color;
		
		cindex++;
		index+=4;
		row++;
		if (row == map_width) {row = 0; index+=((512-map_width)*4);}
	}
	
	//Change palette on gui
	glBindTexture(GL_TEXTURE_2D, texture_gui0);
	glTexSubImage2D(GL_TEXTURE_2D,0,128,0,8,2,GL_RGB,GL_UNSIGNED_BYTE,map_palette);
}

void Update_Palette(){
	int x,y;
	int index = 0, cindex = 0;
	Color3b *palette;
	if(!EGA_MODE) palette = map_palette;
	if(EGA_MODE) {
		palette = map_palette_EGA_Temp;
		for (y = 0;y != 16; y++) palette[y] = EGA_pal[map_palette_EGA[y]];
	}
	
	//Update palette on map
	for (y = 0; y < map_height; y++){
		for (x = 0; x < map_width; x++){
			cindex = (y*512)+x;
			index = cindex*4;
			Color3b color = palette[map_bgcolor[cindex]];
			bg_vertices.col[index  ] = color;
			bg_vertices.col[index+1] = color;
			bg_vertices.col[index+2] = color;
			bg_vertices.col[index+3] = color;
			
			color = palette[map_fgcolor[cindex]];
			fg_vertices.col[index  ] = color;
			fg_vertices.col[index+1] = color;
			fg_vertices.col[index+2] = color;
			fg_vertices.col[index+3] = color;
		}
	}
	
	//Change palette on gui
	glBindTexture(GL_TEXTURE_2D, texture_gui0);
	glTexSubImage2D(GL_TEXTURE_2D,0,128,0,8,2,GL_RGB,GL_UNSIGNED_BYTE,palette);
}


//EDITOR
void Set_Tiles(int x, int y, int tile, int bcol, int fcol){
	int vindex = ((y<<9)+x)<<2;
	int tilex = tile&15;
	int tiley = tile>>4;
	Color3b *palette;
	if(!EGA_MODE) palette = map_palette;
	if(EGA_MODE) palette = map_palette_EGA_Temp;

	Color3b bcolor = palette[bcol];
	Color3b fcolor = palette[fcol];
	
	fg_vertices.coord[vindex  ] = (TexCoord2f) {tilex*tex_cel  ,tiley*tex_cel  };
	fg_vertices.coord[vindex+1] = (TexCoord2f) {(tilex*tex_cel)+tex_cel,tiley*tex_cel  };
	fg_vertices.coord[vindex+2] = (TexCoord2f) {(tilex*tex_cel)+tex_cel,(tiley*tex_cel)+tex_cel};
	fg_vertices.coord[vindex+3] = (TexCoord2f) {tilex*tex_cel  ,(tiley*tex_cel)+tex_cel};
	
	
	fg_vertices.col[vindex  ] = fcolor;
	fg_vertices.col[vindex+1] = fcolor;
	fg_vertices.col[vindex+2] = fcolor;
	fg_vertices.col[vindex+3] = fcolor;
	
	bg_vertices.col[vindex  ] = bcolor;
	bg_vertices.col[vindex+1] = bcolor;
	bg_vertices.col[vindex+2] = bcolor;
	bg_vertices.col[vindex+3] = bcolor;
	
	map_char[(y*512)+x] = tile;
	map_bgcolor[(y*512)+x] = bcol;
	map_fgcolor[(y*512)+x] = fcol;
}

void Get_Tiles(int x, int y, int sizex, int sizey){
	Get_Tile_Group = 0;
	if (sizex!=0) Get_Tile_Group = 1;
	if (sizey!=0) Get_Tile_Group = 1;
	
	if(!Get_Tile_Group){
		buffer_tiles[0] = map_char[(y*512)+x];
		buffer_bgcolor[0] = map_bgcolor[(y*512)+x];
		buffer_fgcolor[0] = map_fgcolor[(y*512)+x];
	} else {
		int line = 0, offset = 0, sx = 0;
		if (sizex <  0) GTX = x;
		if (sizex == 0) GTX = Get_Tile_X;
		if (sizex >  0) GTX = Get_Tile_X;
		if (sizey <  0) GTY = y;
		if (sizey == 0) GTY = Get_Tile_Y;
		if (sizey >  0) GTY = Get_Tile_Y;
		sx = abs(sizex)+1;
		for (line =0; line < abs(sizey)+1; line++){
			memcpy(&buffer_tiles[offset],&map_char[(GTY*512)+GTX],sx);
			memcpy(&buffer_bgcolor[offset],&map_bgcolor[(GTY*512)+GTX],sx);
			memcpy(&buffer_fgcolor[offset],&map_fgcolor[(GTY*512)+GTX],sx);
			GTY++;offset+=sx;
		}
		GTY-=line;
		int index = (GTY<<11)+(GTX<<2);
		int index2 = 0;
		int line2 = 0;
		for (line2 = 0;line2 < abs(sizey)+1; line2++){
			memcpy(&bg_buffer_vertices.col[index2],&bg_vertices.col[index],(((abs(sizex))<<2) + 4)*sizeof(Color3b));
			memcpy(&fg_buffer_vertices.coord[index2],&fg_vertices.coord[index],(((abs(sizex))<<2) + 4)*sizeof(TexCoord2f));
			memcpy(&fg_buffer_vertices.col[index2],&fg_vertices.col[index],(((abs(sizex))<<2) + 4)*sizeof(Color3b));
			index+=512*4;index2+=512*4;
		}
	}
}

void Edit_Tiles(){
	//paste tile or group of tiles
	if (Set_Tile){
		if(!Get_Tile_Group){
			int x = ((-SCR_X-sx1+sx0+mx)>>3)<<3;
			int y = ((-SCR_Y-sy1+sy0+my)>>3)<<3;
			if ((x > -1) && (y > -1) && (x < map_width*8) && (y < map_height*8)){
				start_type_tile_X = x>>3;
				type_tile_X = x>>3;type_tile_Y = y>>3;
				Set_Tiles(x>>3,y>>3,buffer_tiles[0],buffer_bgcolor[0],buffer_fgcolor[0]);
			}
		} else {
			int x = ((-SCR_X-sx1+sx0+mx)>>3)<<3;
			int y = ((-SCR_Y-sy1+sy0+my)>>3)<<3;
			int ox = 0, oy = 0, offset = 0;
			int s_x = abs(sizex/2);
			int s_y = abs(sizey/2);
			if ((x > -1) && (y > -1) && (x < map_width*8) && (y < map_height*8)){
				for (oy = 0; oy < abs(sizey)+1; oy++){
					for (ox = 0; ox < abs(sizex)+1; ox++){
						int ax = (x>>3)-s_x+ox;
						int ay = (y>>3)-s_y+oy;
						if ((ax > -1)&&(ax<map_width)&&(ay>-1)&&(ay<map_height)){
							Set_Tiles(ax,ay,buffer_tiles[offset],buffer_bgcolor[offset],buffer_fgcolor[offset]);
						}
						offset++;
					}
				}
			}
		}
	}	
}


//OPEN GL
void drawString(float x, float y, char *string) {
	glColor3f(0,0,0);
	glRasterPos3i(x, y, 0);
	glLoadIdentity();
	int s = strlen(string);
	for (int c = 0; c != s; c++) {
		//glutStrokeCharacter(GLUT_STROKE_ROMAN, string[c]);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,string[c]);  // Updates the position
	}
}

void Create_OpenGL_Quad(cell_vertex *vertices,int vindex, int x, int y, int z, int x1, int y1, float cx, float cy, float cx1, float cy1){
	vertices->coord[vindex] = (TexCoord2f){cx, cy};
	vertices->coord[vindex+1] = (TexCoord2f){cx1, cy};
	vertices->coord[vindex+2] = (TexCoord2f){cx1, cy1};
	vertices->coord[vindex+3] = (TexCoord2f){cx, cy1};
	
	vertices->pos[vindex] = (Vertex3s){x,y,z};
	vertices->pos[vindex+1] = (Vertex3s){x1,y,z};
	vertices->pos[vindex+2] = (Vertex3s){x1,y1,z};
	vertices->pos[vindex+3] = (Vertex3s){x,y1,z};
	
	vertices->col[vindex  ] = (Color3b){25,25,25};
	vertices->col[vindex+1] = (Color3b){25,25,25};
	vertices->col[vindex+2] = (Color3b){25,25,25};
	vertices->col[vindex+3] = (Color3b){25,25,25};
}

void Create_OpenGL_Quad_1(cell_vertex_1 *vertices,int vindex, int x, int y, int z, int x1, int y1, float cx, float cy, float cx1, float cy1){

	vertices->pos[vindex] = (Vertex3s){x,y,z};
	vertices->pos[vindex+1] = (Vertex3s){x1,y,z};
	vertices->pos[vindex+2] = (Vertex3s){x1,y1,z};
	vertices->pos[vindex+3] = (Vertex3s){x,y1,z};
	
	vertices->col[vindex  ] = (Color3b){64,64,64};
	vertices->col[vindex+1] = (Color3b){64,64,64};
	vertices->col[vindex+2] = (Color3b){64,64,64};
	vertices->col[vindex+3] = (Color3b){64,64,64};
}

void Create_Quad_Arrays(){
	int x,y,z,cell_pos_x,cell_pos_y;
	int vindex = 0, offset = 0;
	
	//create bkg
	bg_vertices.pos = (Vertex3s*) calloc (4*512*512,sizeof(Vertex3s));
	bg_vertices.col = (Color3b*) calloc (4*512*512,sizeof(Color3b));
	bg_buffer_vertices.pos = (Vertex3s*) calloc (4*512*512,sizeof(Vertex3s));
	bg_buffer_vertices.col = (Color3b*) calloc (4*512*512,sizeof(Color3b));
	x=0; y=0; vindex = 0;
	for (y = 0; y < 512; y++){
		for (x = 0; x < 512; x++){
			cell_pos_x = x<<3;cell_pos_y = y<<3;
			Create_OpenGL_Quad_1(&bg_vertices,vindex,cell_pos_x,cell_pos_y,0,cell_pos_x+8,cell_pos_y+8,0,0,0,0);
			Create_OpenGL_Quad_1(&bg_buffer_vertices,vindex,cell_pos_x,cell_pos_y,0,cell_pos_x+8,cell_pos_y+8,0,0,0,0);
			vindex+=4;
		}
	}
	
	//create fg and collision maps
	fg_vertices.coord = (TexCoord2f*) calloc (4*512*512,sizeof(TexCoord2f));
	fg_vertices.pos = (Vertex3s*) calloc (4*512*512,sizeof(Vertex3s));
	fg_vertices.col = (Color3b*) calloc (4*512*512,sizeof(Color3b));
	fg_buffer_vertices.coord = (TexCoord2f*) calloc (4*512*512,sizeof(TexCoord2f));
	fg_buffer_vertices.pos = (Vertex3s*) calloc (4*512*512,sizeof(Vertex3s));
	fg_buffer_vertices.col = (Color3b*) calloc (4*512*512,sizeof(Color3b));
	collision_vertices.coord = (TexCoord2f*) calloc (4*512*512,sizeof(TexCoord2f));
	collision_vertices.pos = (Vertex3s*) calloc (4*512*512,sizeof(Vertex3s));
	grid_vertices.pos = (Vertex3s*) calloc (4*512*512,sizeof(Vertex3s));
	x=0; y=0; vindex = 0;
	for (y = 0; y < 512; y++){
		for (x = 0; x < 512; x++){
			cell_pos_x = x<<3;cell_pos_y = y<<3;
			Create_OpenGL_Quad(&fg_vertices,vindex,cell_pos_x,cell_pos_y,0,cell_pos_x+8,cell_pos_y+8,0,0,0,0);
			Create_OpenGL_Quad(&fg_buffer_vertices,vindex,cell_pos_x,cell_pos_y,0,cell_pos_x+8,cell_pos_y+8,0,0,0,0);
			vindex+=4;
		}
	}

	//create gui
	vindex = 0;
	gui_vertices.coord = (TexCoord2f*) g_coord;
	gui_vertices.pos = (Vertex3s*) g_pos;
	gui_vertices.col = (Color3b*) calloc (4*15,sizeof(Color3b));
	for (x=0;x<4*15;x++){
		gui_vertices.col[vindex] = (Color3b){255,255,255};
		vindex++;
	}
	
	//create selected tile
	select_vertices.coord = (TexCoord2f*) calloc (4,sizeof(TexCoord2f));
	select_vertices.pos = (Vertex3s*) calloc (4,sizeof(Vertex3s));
	select_vertices_2.pos = (Vertex3s*) calloc (4,sizeof(Vertex3s));
	select_vertices.col = (Color3b*) calloc (4,sizeof(Color3b));
	Create_OpenGL_Quad(&select_vertices,0,0,0,0,8,8,0,0,1,1);
	
	vindex = 0;
	//Create map chunks indices
	map_chunk_index = (unsigned int*) calloc (1024*4 *256,sizeof(unsigned int));
	for (z = 0; z < 256; z++){
		int vx = z&15; int vy = z>>4;
		vindex = (vy*512*32*4) + (vx*32*4);
		for (y = 0; y < 32; y++){
			for (x = 0; x < 32; x++){
				map_chunk_index[offset++] = vindex++;
				map_chunk_index[offset++] = vindex++;
				map_chunk_index[offset++] = vindex++;
				map_chunk_index[offset++] = vindex++;
			}
			vindex+= 4*(512-32);
		}
	}
}

void Draw_Map(){
	int x = 0, y = 0, chunk =32*32*4;

	glLoadIdentity();
	glTranslatef((SCR_X+sx1-sx0),(SCR_Y+sy1-sy0),0);
	glColor3f( 1.0, 1.0, 1.0 );
	
	//Render BG
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_INDEX_ARRAY);
	glDisable(GL_TEXTURE_2D);
	glVertexPointer(3, GL_SHORT, sizeof(Vertex3s), bg_vertices.pos);
	glIndexPointer(GL_SHORT, sizeof(short), map_chunk_index);
	glColorPointer(3,GL_UNSIGNED_BYTE, sizeof(Color3b), bg_vertices.col);
	for (y = abs(SCR_Y+sy1-sy0)>>8;y < (abs(SCR_Y+sy1-sy0)>>8)+3;y++){
		for (x = abs(SCR_X+sx1-sx0)>>8;x < (abs(SCR_X+sx1-sx0)>>8)+3;x++){
			if (x > 15) break;
			if (y > 15) break;
			glDrawElements(GL_QUADS,chunk,GL_UNSIGNED_INT,&map_chunk_index[((y<<4)+x)*chunk]);
		}
	}
	
	//Render FG
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glBindTexture(GL_TEXTURE_2D, texture_tiles);
	glVertexPointer(3, GL_SHORT, sizeof(Vertex3s), fg_vertices.pos);
	glTexCoordPointer(2, GL_FLOAT, sizeof(TexCoord2f), fg_vertices.coord);
	glColorPointer(3,GL_UNSIGNED_BYTE, sizeof(Color3b), fg_vertices.col);
	for (y = abs(SCR_Y+sy1-sy0)>>8;y < (abs(SCR_Y+sy1-sy0)>>8)+3;y++){
		for (x = abs(SCR_X+sx1-sx0)>>8;x < (abs(SCR_X+sx1-sx0)>>8)+3;x++){
			if (x > 15) break;
			if (y > 15) break;
			glDrawElements(GL_QUADS,chunk,GL_UNSIGNED_INT,&map_chunk_index[((y<<4)+x)*chunk]);
		}
	}
	glDisableClientState(GL_INDEX_ARRAY);
	
	//Draw Grid
	if (grid_state){
		glDisable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		glLoadIdentity();
		glTranslatef(56+((SCR_X+sx1-sx0)&7),-8+((SCR_Y+sy1-sy0)&7),0);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glColor4f(grid_color.r/256.0,grid_color.g/256.0,grid_color.b/256.0, 0.4f);
		glBegin(GL_LINES);
		for(int y=0; y!=96*8; y+=8){
			glVertex3s(0, y, 0);
			glVertex3s(1024, y, 0);
		}
		for(int x=0; x!=96*8; x+=8){
			glVertex3s(x, 0, 0);
			glVertex3s(x,1024, 0);
		}
		glEnd();
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
	}
}

void Draw_Select(){
	mx = mouse_x/gui_scale;
	my = mouse_y/gui_scale;
	int x = ((-SCR_X-sx1+sx0+mx)>>3)<<3;
	int y = ((-SCR_Y-sy1+sy0+my)>>3)<<3;
	int translate_x = 0;
	int translate_y = 0;
	Color3b *palette;
	if(!EGA_MODE) palette = map_palette;
	if(EGA_MODE) palette = map_palette_EGA_Temp;
	
	tile_X = x>>3;
	tile_Y = y>>3;
	if (tile_X < 0) {tile_X = 0; x = 0;}
	if (tile_Y < 0) {tile_Y = 0; y = 0;}
	if (tile_X > map_width-1) {tile_X = map_width-1;x = (map_width-1)<<3;}
	if (tile_Y > map_height-1) {tile_Y = map_height-1;y = (map_height-1)<<3;}
	
	if (Get_Tile == 0){
		if (!Get_Tile_Group){
			int tilex = buffer_tiles[0]&15;
			int tiley = buffer_tiles[0]>>4;
			float tx = tilex*tex_cel;
			float ty = tiley*tex_cel;
			float crop = 0.000976;
			Create_OpenGL_Quad(&select_vertices,0,0,0,0,8,8,0,0,1,1);
	
			select_vertices.coord[0] = (TexCoord2f) {tx+crop,ty+crop};
			select_vertices.coord[1] = (TexCoord2f) {tx+tex_cel-crop,ty+crop};
			select_vertices.coord[2] = (TexCoord2f) {tx+tex_cel-crop,ty+tex_cel-crop};
			select_vertices.coord[3] = (TexCoord2f) {tx+crop,ty+tex_cel-crop};
			
			glDisableClientState(GL_COLOR_ARRAY);
			glTexCoordPointer(2, GL_FLOAT, sizeof(TexCoord2f), select_vertices.coord);
			
			//SELECTED TILE OVER MAP
			glVertexPointer(3, GL_SHORT, sizeof(Vertex3s), select_vertices.pos);
			glLoadIdentity();
			glTranslatef(SCR_X+sx1-sx0+x,SCR_Y+sy1-sy0+y,0);
			//Render bg
			glDisable(GL_TEXTURE_2D);
			Color3b color = palette[buffer_bgcolor[0]];
			glColor3ub(color.r,color.g,color.b);
			if (mouse_x > 255 && mouse_x < SCREEN_WIDTH-16 && mouse_y < SCREEN_HEIGHT-16)
				glDrawArrays(GL_QUADS, 0, 4);
			glEnable(GL_TEXTURE_2D);
			//Render fg
			color = palette[buffer_fgcolor[0]];
			glColor3ub(color.r,color.g,color.b);
			glBindTexture(GL_TEXTURE_2D, texture_tiles);
			if (mouse_x > 255 && mouse_x < SCREEN_WIDTH-16 && mouse_y < SCREEN_HEIGHT-16)
				glDrawArrays(GL_QUADS,0, 4);
			
			//GUI SELECTED/COPIED TILE
			glLoadIdentity();
			glTranslatef(200*map_scale,192*2*map_scale,0);
			glScalef(6*map_scale,6*map_scale,1);
			//Render bg
			glDisable(GL_TEXTURE_2D);
			color = palette[buffer_bgcolor[0]];
			glColor3ub(color.r,color.g,color.b);
			glDrawArrays(GL_QUADS, 0, 4);
			glEnable(GL_TEXTURE_2D);
			//Render fg
			color = palette[buffer_fgcolor[0]];
			glColor3ub(color.r,color.g,color.b);
			glBindTexture(GL_TEXTURE_2D, texture_tiles);
			glDrawArrays(GL_QUADS,0, 4);
			
			glEnableClientState(GL_COLOR_ARRAY);
		} else {
			int selection_y = 0;
			int s_x = abs((sizex/2)*8);
			int s_y = abs((sizey/2)*8);
			int map_index = 0;
			glColor3f( 1.0, 1.0, 1.0 );
			glLoadIdentity();
			glTranslatef(SCR_X+sx1-sx0+x-s_x,SCR_Y+sy1-sy0+y-s_y,0);
			
			//Render BG
			glDisableClientState(GL_TEXTURE_COORD_ARRAY);
			glDisable(GL_TEXTURE_2D);
			glVertexPointer(3, GL_SHORT, sizeof(Vertex3s), bg_buffer_vertices.pos);
			glColorPointer(3,GL_UNSIGNED_BYTE, sizeof(Color3b), bg_buffer_vertices.col);
			for (selection_y = 0;selection_y < abs(sizey)+1; selection_y++){
				glDrawArrays(GL_QUADS,4*map_index, (4*abs(sizex)) + 4);
				map_index+=512;
			}
			//Render FG
			glEnable(GL_TEXTURE_2D);
			glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			
			glBindTexture(GL_TEXTURE_2D, texture_tiles);
			glVertexPointer(3, GL_SHORT, sizeof(Vertex3s), fg_buffer_vertices.pos);
			glTexCoordPointer(2, GL_FLOAT, sizeof(TexCoord2f), fg_buffer_vertices.coord);
			glColorPointer(3,GL_UNSIGNED_BYTE, sizeof(Color3b), fg_buffer_vertices.col);
			map_index = 0;
			for (selection_y = 0;selection_y < abs(sizey)+1; selection_y++){
				glDrawArrays(GL_QUADS,4*map_index, (4*abs(sizex)) + 4);
				map_index+=512;
			}
		}
	}
	if (Get_Tile == 1){
		Get_Tile_X = tile_X;Get_Tile_Y = tile_Y;
		Get_Tile++; 
	}
	if (Get_Tile == 2){
		sizex = tile_X - Get_Tile_X;
		sizey = tile_Y - Get_Tile_Y;
		sizx = abs(sizex)+1;
		sizy = abs(sizey)+1;
		translate_x = 0;
		translate_y = 0;
		
		Get_Tiles(tile_X,tile_Y,sizex,sizey);

		select_vertices_2.pos[0] = (Vertex3s) {0,0,0};
		select_vertices_2.pos[1] = (Vertex3s) {sizx*8,0,0};
		select_vertices_2.pos[2] = (Vertex3s) {sizx*8,sizy*8,0};
		select_vertices_2.pos[3] = (Vertex3s) {0,sizy*8,0};
		
		if (sizex > 0) translate_x = -sizex*8;
		if (sizey > 0) translate_y = -sizey*8;
		
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisable(GL_TEXTURE_2D);
		glLoadIdentity();
		glTranslatef(SCR_X+sx1-sx0+x+translate_x,SCR_Y+sy1-sy0+y+translate_y,0);
		glColor4f( 0.7, 0.7, 1.0 , 0.3);
		glVertexPointer(3, GL_SHORT, sizeof(Vertex3s), select_vertices_2.pos);
		
		glDrawArrays(GL_QUADS, 0, 4);
		
		glEnable(GL_TEXTURE_2D);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
	}
	
}

void Move_Pal_Tile_Selection(){
	int pos;
	int bx =  16 + ((buffer_bgcolor[0]&7)*28);
	int by = 328 + ((buffer_bgcolor[0]/8)*24);
	int fx =  16 + ((buffer_fgcolor[0]&7)*28);
	int fy = 328 + ((buffer_fgcolor[0]/8)*24);
	//BG on palette
	pos = 5*4;
	gui_vertices.pos[pos] = (Vertex3s) {bx,by,0};
	gui_vertices.pos[pos+1] = (Vertex3s) {bx+32,by,0};
	gui_vertices.pos[pos+2] = (Vertex3s) {bx+32,by+32,0};
	gui_vertices.pos[pos+3] = (Vertex3s) {bx,by+32,0};
	
	//FG on palette
	pos = 6*4;
	gui_vertices.pos[pos] = (Vertex3s) {fx,fy,0};
	gui_vertices.pos[pos+1] = (Vertex3s) {fx+32,fy,0};
	gui_vertices.pos[pos+2] = (Vertex3s) {fx+32,fy+32,0};
	gui_vertices.pos[pos+3] = (Vertex3s) {fx,fy+32,0};
	
	//Tile selected on tileset
	pos = 7*4;
	fx = ((buffer_tiles[0]&15)*16)-8;
	fy = (((buffer_tiles[0]/16)*16)+64)-8;
	gui_vertices.pos[pos] = (Vertex3s) {fx,fy,0};
	gui_vertices.pos[pos+1] = (Vertex3s) {fx+32,fy,0};
	gui_vertices.pos[pos+2] = (Vertex3s) {fx+32,fy+32,0};
	gui_vertices.pos[pos+3] = (Vertex3s) {fx,fy+32,0};
	
	//cycle color
	switch (cycle_color_state){
		case 0: sel_tile_col.b++; if (sel_tile_col.b == 255) cycle_color_state = 1; break;
		case 1: sel_tile_col.r--; if (sel_tile_col.r ==   0) cycle_color_state = 2; break;
		case 2: sel_tile_col.g++; if (sel_tile_col.g == 255) cycle_color_state = 3; break;
		case 3: sel_tile_col.b--; if (sel_tile_col.b ==   0) cycle_color_state = 4; break;
		case 4: sel_tile_col.r++; if (sel_tile_col.r == 255) cycle_color_state = 5; break;
		case 5: sel_tile_col.g--; if (sel_tile_col.g ==   0) cycle_color_state = 0; break;
	}
	gui_vertices.col[pos  ] = sel_tile_col;
	gui_vertices.col[pos+1] = sel_tile_col;
	gui_vertices.col[pos+2] = sel_tile_col;
	gui_vertices.col[pos+3] = sel_tile_col;
}

void Change_Palette_Icon_EGA_VGA(){
	int pos = 4*12;
	if (!EGA_MODE){
		gui_vertices.coord[pos] =   (TexCoord2f) {6.0/8.0,1.0/8.0};
		gui_vertices.coord[pos+1] = (TexCoord2f) {7.0/8.0,1.0/8.0};
		gui_vertices.coord[pos+2] = (TexCoord2f) {7.0/8.0,2.0/8.0};
		gui_vertices.coord[pos+3] = (TexCoord2f) {6.0/8.0,2.0/8.0};
	} else {
		gui_vertices.coord[pos] =   (TexCoord2f) {7.0/8.0,1.0/8.0};
		gui_vertices.coord[pos+1] = (TexCoord2f) {8.0/8.0,1.0/8.0};
		gui_vertices.coord[pos+2] = (TexCoord2f) {8.0/8.0,2.0/8.0};
		gui_vertices.coord[pos+3] = (TexCoord2f) {7.0/8.0,2.0/8.0};
	}
}

void Draw_Gui(){
	int t = GL_TEXTURE_2D; int r = GL_RGBA; int u = GL_UNSIGNED_BYTE;
	
	Move_Pal_Tile_Selection();
	
	glLoadIdentity();
	glTranslatef(0,0,0);
	glScalef(map_scale,map_scale,1);
	
	unsigned char dec;
	unsigned char tile = buffer_tiles[0];
	int mw; int mh;
	unsigned char b = buffer_bgcolor[0]; 
	unsigned char f = buffer_fgcolor[0]; 
	
	//glTexSubImage2D updates part of a texture, in this case
	//we are displaying and updating gui_pixels, a 256x256 texture
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(t, texture_gui0);
	
	//Update palette number
	glTexSubImage2D(t,0,48,192,16,16,r,u,&binary_numbers_data_start[b*1024]);
	glTexSubImage2D(t,0,64,192,16,16,r,u,&binary_numbers_data_start[f*1024]);
	
	//Update tile number
	dec = tile % 10; tile /=10; glTexSubImage2D(t,0,168,192,16,16,r,u,&binary_numbers_data_start[dec*1024]);
	dec = tile % 10; tile /=10; glTexSubImage2D(t,0,152,192,16,16,r,u,&binary_numbers_data_start[dec*1024]);
	dec = tile;                 glTexSubImage2D(t,0,136,192,16,16,r,u,&binary_numbers_data_start[dec*1024]);
	
	//Update tile pos
	dec = tile_X % 10; tile_X /=10; glTexSubImage2D(t,0,168,221,16,16,r,u,&binary_numbers_data_start[dec*1024]);
	dec = tile_X % 10; tile_X /=10; glTexSubImage2D(t,0,152,221,16,16,r,u,&binary_numbers_data_start[dec*1024]);
	dec = tile_X;                   glTexSubImage2D(t,0,136,221,16,16,r,u,&binary_numbers_data_start[dec*1024]);
	dec = tile_Y % 10; tile_Y /=10; glTexSubImage2D(t,0,168,237,16,16,r,u,&binary_numbers_data_start[dec*1024]);
	dec = tile_Y % 10; tile_Y /=10; glTexSubImage2D(t,0,152,237,16,16,r,u,&binary_numbers_data_start[dec*1024]);
	dec = tile_Y;                   glTexSubImage2D(t,0,136,237,16,16,r,u,&binary_numbers_data_start[dec*1024]);
	
	//Update map size X 
	mw = map_w;
	dec = mw % 10; mw /=10; glTexSubImage2D(t,0,80,221,16,16,r,u,&binary_numbers_data_start[dec*1024]);
	dec = mw % 10; mw /=10; glTexSubImage2D(t,0,64,221,16,16,r,u,&binary_numbers_data_start[dec*1024]);
	dec = mw;				glTexSubImage2D(t,0,48,221,16,16,r,u,&binary_numbers_data_start[dec*1024]);
	if (setting_width == 1) {
		if (setting_blink > 15){
			glTexSubImage2D(t,0,80,221,16,16,r,u,&binary_numbers_data_start[16*1024]);
			glTexSubImage2D(t,0,64,221,16,16,r,u,&binary_numbers_data_start[16*1024]);
			glTexSubImage2D(t,0,48,221,16,16,r,u,&binary_numbers_data_start[16*1024]);
		}
		setting_blink++; 
		if(setting_blink == 32)	setting_blink = 0;	
	}

	//Update map size Y
	mh = map_h;
	dec = mh % 10; mh /=10; glTexSubImage2D(t,0,80,237,16,16,r,u,&binary_numbers_data_start[dec*1024]);
	dec = mh % 10; mh /=10; glTexSubImage2D(t,0,64,237,16,16,r,u,&binary_numbers_data_start[dec*1024]);
	dec = mh;				glTexSubImage2D(t,0,48,237,16,16,r,u,&binary_numbers_data_start[dec*1024]);
	if (setting_height == 1) {
		if(setting_blink>15){
			glTexSubImage2D(t,0,80,237,16,16,r,u,&binary_numbers_data_start[16*1024]);
			glTexSubImage2D(t,0,64,237,16,16,r,u,&binary_numbers_data_start[16*1024]);
			glTexSubImage2D(t,0,48,237,16,16,r,u,&binary_numbers_data_start[16*1024]);
		}
		setting_blink++; 
		if(setting_blink == 32)	setting_blink = 0;	
	}
	
	//setting_height==0){

	//Draw gui
	glColor3f( 1.0, 1.0, 1.0 );
	glVertexPointer(3, GL_SHORT, sizeof(Vertex3s), gui_vertices.pos);
	glTexCoordPointer(2, GL_FLOAT, sizeof(TexCoord2f), gui_vertices.coord);
	glColorPointer(3,GL_UNSIGNED_BYTE, sizeof(Color3b), gui_vertices.col);
	glDrawArrays(GL_QUADS,0,4*15);

	//Draw light on button
	if (mouse_y>23 && mouse_y<56){
		if (mouse_x> 15 && mouse_x<48)button_x = 16;
		else if (mouse_x> 47 && mouse_x<80)button_x = 48;
		else if (mouse_x> 79 && mouse_x<112)button_x = 80;
		else if (mouse_x>111 && mouse_x<144)button_x = 112;
		else if (mouse_x>143 && mouse_x<176)button_x = 144;
		//else if (mouse_x>175 && mouse_x<208)button_x = 176;
		else if (mouse_x>207 && mouse_x<240)button_x = 208;
		else button_x = -48;
	} else button_x = -48;
	glBegin(GL_QUADS);
		glTexCoord2f( 9.0*1.0/16.0,0);        glVertex3s(button_x   ,24,0);
		glTexCoord2f(10.0*1.0/16.0,0);        glVertex3s(button_x+32,24,0);
		glTexCoord2f(10.0*1.0/16.0,1.0/16.0); glVertex3s(button_x+32,24+32,0);
		glTexCoord2f( 9.0*1.0/16.0,1.0/16.0); glVertex3s(button_x   ,24+32,0);
	glEnd();
	
	//Draw tileset Grid
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
	glLoadIdentity();
	glScalef(G_scale[(SCALE+1)&1],G_scale[(SCALE+1)&1],1);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glColor4f(0.3,0.3,0.6,0.5);
	glBegin(GL_LINES);
	for(int y=8; y!=40; y+=2){
		glVertex3s(0, y, 0);
		glVertex3s(32, y, 0);
	}
	for(int x=0; x!=32; x+=2){
		glVertex3s(x, 8, 0);
		glVertex3s(x,40, 0);
	}
	glEnd();
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(t, texture_gui0);
	glLoadIdentity();
	glTranslatef(0,0,0);
	glScalef(map_scale,map_scale,1);
	glColor4f(1,1,1,1);
	
	//Draw ega select palette
	if(EDITTING_EGA_PALETTE){
		glBegin(GL_QUADS);
			glTexCoord2f(16.0/32.0,1.0/32.0); glVertex3s( 16,272,0);
			glTexCoord2f(17.0/32.0,1.0/32.0); glVertex3s(240,272,0);
			glTexCoord2f(17.0/32.0,2.0/32.0); glVertex3s(240,272+192,0);
			glTexCoord2f(16.0/32.0,2.0/32.0); glVertex3s( 16,272+192,0);
		glEnd();
	}

	//Draw scroll bars mouse_x mouse_y
	glBegin(GL_QUADS);
		glTexCoord2f( 8.0/16.0,7.0/16.0); glVertex3s(256,SCREEN_HEIGHT-16,0);
		glTexCoord2f( 9.0/16.0,7.0/16.0); glVertex3s(SCREEN_WIDTH-16,SCREEN_HEIGHT-16,0);
		glTexCoord2f( 9.0/16.0,8.0/16.0); glVertex3s(SCREEN_WIDTH-16,SCREEN_HEIGHT,0);
		glTexCoord2f( 8.0/16.0,8.0/16.0); glVertex3s(256,SCREEN_HEIGHT,0);
	glEnd();
	
	
	glBegin(GL_QUADS);
		glTexCoord2f( 9.0/16.0,7.0/16.0); glVertex3s(SCREEN_WIDTH-16,0,0);
		glTexCoord2f(10.0/16.0,7.0/16.0); glVertex3s(SCREEN_WIDTH,0,0);
		glTexCoord2f(10.0/16.0,8.0/16.0); glVertex3s(SCREEN_WIDTH,SCREEN_HEIGHT-16,0);
		glTexCoord2f( 9.0/16.0,8.0/16.0); glVertex3s(SCREEN_WIDTH-16,SCREEN_HEIGHT-16,0);
	glEnd();

	glBindTexture(t,0);
}

void display(){
	glClearColor(0.16f, 0.16f, 0.16f, 0.f);
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0,SCREEN_WIDTH,SCREEN_HEIGHT,0, 0, 1);
	glScalef(gui_scale,gui_scale,1);
	
	glMatrixMode(GL_MODELVIEW);
	Draw_Map();
	Draw_Gui();
	Draw_Select();
	Edit_Tiles();
	Sleep(8);//to avoid high CPU usage
	glutSwapBuffers();
}

void OpenGl_Init( int argc, char *argv[] ){
	glutInit( &argc, argv );
	//Initialize window system
	glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);
	glutCreateWindow("-GA TEXT MAP EDITOR (CGA/TANDY/EGA/VGA)");
	//glutFullScreen();
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA); // = color * alpha + background * (1-alpha)
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//glEnable(GL_ALPHA_TEST);
	//glAlphaFunc(GL_NOTEQUAL, 0);
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glScissor(0,0,SCREEN_WIDTH,SCREEN_HEIGHT); 
	glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
	
	glGenTextures(1,&texture_gui0);
	glBindTexture(GL_TEXTURE_2D, texture_gui0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,256,256, 0, GL_RGBA, GL_UNSIGNED_BYTE, binary_gui0_data_start);	
}

void resize(int width, int height) {
    // we ignore the params and do:
	//glutReshapeWindow(SCREEN_WIDTH,SCREEN_HEIGHT);
	SCREEN_WIDTH = glutGet(GLUT_WINDOW_WIDTH);
	SCREEN_HEIGHT = glutGet(GLUT_WINDOW_HEIGHT);
	glScissor(0,0,SCREEN_WIDTH,SCREEN_HEIGHT); 
	glViewport(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
}


//CONTROLS
void mouse_click(int button,int state,int x,int y){
	//Controls
	if (setting_width == 0 && setting_height == 0){
	switch(button){
		case GLUT_LEFT_BUTTON:
			if(state==GLUT_DOWN){
				if (mouse_x > 256){
					if (mouse_x < SCREEN_WIDTH-16 && mouse_y < SCREEN_HEIGHT-16)
						Set_Tile = 1;
				} else {
					//set bg pal
					if ((mouse_x>15)&&(mouse_x<240)&&(mouse_y>327)&&(mouse_y<376)){
						buffer_bgcolor[0] = (((mouse_y-328)/24)*8)+((mouse_x-16)/28);
					}
					//select tile
					if ((mouse_y>64)&&(mouse_y<256+64)){
						buffer_tiles[0] = (((mouse_y-64)>>4)*16)+(mouse_x>>4);
					}
					
					if (mouse_x>48 && mouse_x<96){
						//set map width
						if (mouse_y>413 && mouse_y<429){setting_width = 1;map_w = 0;}
						//set map height
						if (mouse_y>430 && mouse_y<446){setting_height = 1;map_h = 0;}
					}
				}
			}
			if(state==GLUT_UP){
				Set_Tile = 0;
				//GUI BUTTONS
				if (mouse_y>23 && mouse_y<56){
					if (mouse_x> 15 && mouse_x<48)Load_Map(1);
					if (mouse_x> 47 && mouse_x<80)Save_Map();
					if (mouse_x> 79 && mouse_x<112)Load_Tileset();
					if (mouse_x>111 && mouse_x<144)Export_EGA_VGA_Tileset();
					if (mouse_x>143 && mouse_x<176 && !EGA_MODE)Load_Palette();
					//else if (mouse_x>175 && mouse_x<208)Enable_ColMap;
					else if (mouse_x>207 && mouse_x<240){grid_state++;grid_state&=1;}
				}
			}
		break;
		case GLUT_MIDDLE_BUTTON:
			if (mouse_x > 256){
				if (mouse_x < SCREEN_WIDTH-16 && mouse_y < SCREEN_HEIGHT-16){
					if(state==GLUT_DOWN){Grab_Map = 1;sx0 = x; sy0 = y; sx0/=gui_scale; sy0/=gui_scale;sx1 = x/gui_scale;sy1 = y/gui_scale;}
					//if(state==GLUT_UP  ){Grab_Map = 0;SCR_X=SCR_X+sx1-sx0;SCR_Y=SCR_Y+sy1-sy0;sx0=0;sy0=0;sx1=0;sy1=0;}
				}
			} else {
				if(state==GLUT_DOWN){
					//edit palette colors
					if (!EGA_MODE){ 
						if (mouse_x>15 && mouse_x<240 && mouse_y>327 && mouse_y<376){
							int color_index = (((mouse_y-328)/24)*8)+((mouse_x-16)/28);
							if(ChooseColor(&cc) == TRUE){
								unsigned char r,g,b; 
								rgbCurrent = cc.rgbResult;//AA RR GG BB
								r = rgbCurrent>>16;
								g = rgbCurrent>>8;
								b = rgbCurrent;
								map_palette[color_index] = (Color3b){b,g,r};
								Update_Palette();
							}
						}
					}
					if (EGA_MODE){
						if (!EDITTING_EGA_PALETTE){
							if (mouse_x>15 && mouse_x<240 && mouse_y>327 && mouse_y<376){
								EDITTING_EGA_PALETTE = 1;
								EGA_selected_color_index = (((mouse_y-328)/24)*8)+((mouse_x-16)/28);
							}
						}
					}
				}
			}
			//Always update map position when releasing wheel
			if(state==GLUT_UP ){
				Grab_Map = 0;
				SCR_X=SCR_X+sx1-sx0;
				SCR_Y=SCR_Y+sy1-sy0;
				sx0=0;sy0=0;sx1=0;sy1=0;
				if (EDITTING_EGA_PALETTE) {
					if (mouse_x>15 && mouse_x<240 && mouse_y>271 && mouse_y<320){
						int color_index = (((mouse_y-272)/24)*8)+((mouse_x-16)/28);
						map_palette_EGA[EGA_selected_color_index] = color_index;
						Update_Palette();
					}
					EDITTING_EGA_PALETTE = 0;
					Update_Palette();
				}
			}
		break;
		case GLUT_RIGHT_BUTTON:
			if(state==GLUT_DOWN){
				if (mouse_x > 256){
					if (mouse_x < SCREEN_WIDTH-16 && mouse_y < SCREEN_HEIGHT-16)
						Get_Tile = 1;
				} else {
					//set fg pal
					if ((mouse_x>15)&&(mouse_x<240)&&(mouse_y>327)&&(mouse_y<376)){
						buffer_fgcolor[0] = (((mouse_y-328)/24)*8)+((mouse_x-16)/28);
					} 
				}
			}
			if(state==GLUT_UP){
				//Change EGA/VGA mode
				if (mouse_y>23 && mouse_y<56){
					if (mouse_x>143 && mouse_x<176){
						switch (EGA_MODE) {
							case 0: EGA_MODE = 1; break;
							case 1: EGA_MODE = 0; break;
							case 2: EGA_MODE = 0; break;
						}
						Change_Palette_Icon_EGA_VGA();
						Update_Palette();
					}
					//set grid color
					if (mouse_x>207 && mouse_x<240){
						if (ChooseColor(&cc) == TRUE){
							unsigned char r,g,b; 
							rgbCurrent = cc.rgbResult;//AA RR GG BB
							r = rgbCurrent>>16;
							g = rgbCurrent>>8;
							b = rgbCurrent;
							grid_color = (Color3b){b,g,r};
						}
					}
				}
				//Exit get tile mode and get tiles or group of tiles
				Get_Tile = 0;
				Create_OpenGL_Quad(&select_vertices,0,0,0,0,8,8,0,0,1,1);
			}
		break;
		default:
		break;
	}
	}
}

void SpecialKeys(int key, int x, int y) {
	switch(key) {
		case GLUT_KEY_F1 :
			switch (Type_ON){
				case 0: Type_ON = 1; break;
				case 1: Type_ON = 0; break;
			}
		break;
	}
}

void NormalKeys(unsigned char key, int x, int y) {
	if (setting_width==0 && setting_height==0){
	//if (key == 27) exit(1);
	//TYPE
	if (key > 32 && Type_ON){
		//if (key > 63) key-=32;
		Set_Tiles(type_tile_X,type_tile_Y,key,buffer_bgcolor[0],buffer_fgcolor[0]);
		type_tile_X++;
		if (type_tile_X > map_width)type_tile_X = 0;
	}
	if (key == 8) {//backspace
		Set_Tiles(type_tile_X-1,type_tile_Y,0,buffer_bgcolor[0],buffer_fgcolor[0]);
		type_tile_X--;
		if (type_tile_X < 0) type_tile_X = 0;
	}
	if (key == 9) {//TAB
		SCALE++;
		map_scale = M_scale[SCALE&1];
		gui_scale = G_scale[SCALE&1];
		if ((SCALE&1) == 0) {SCR_X = 128-(tile_X*8)+((mouse_x-256)/2); SCR_Y = -(tile_Y*8)+((mouse_y)/2);}
		if ((SCALE&1) == 1) {SCR_X = 64-(tile_X*8)+((mouse_x-256)/4); SCR_Y = -(tile_Y*8)+((mouse_y)/4);}
	}
	if (key == 13) {//ENTER CR
		if (type_tile_Y < map_height) {type_tile_Y++;type_tile_X = start_type_tile_X;}
	}
	if (key == 32) {//SPACEBAR
		if (type_tile_X < map_width) type_tile_X++;
	}
	}
	if (setting_width == 1){
		if (key > 47 && key < 58){
			if(setting_digit==0) map_w = (key-48);
			if(setting_digit==1) map_w = (map_w*10)+(key-48);
			if(setting_digit==2) map_w = (map_w*10)+(key-48);
			setting_digit++;
		}
	}
	if (setting_height == 1){
		if (key > 47 && key < 58){
			if(setting_digit==0) map_h = (key-48);
			if(setting_digit==1) map_h = (map_h*10)+(key-48);
			if(setting_digit==2) map_h = (map_h*10)+(key-48);
			setting_digit++;
		}
	}
	if (setting_width==1 || setting_height==1){
		if (key == 13 || setting_digit == 3) {//ENTER CR or 3 digits
			setting_width = 0;
			setting_height = 0;
			setting_digit = 0;
			if (map_w < 1) map_w = map_width;
			if (map_h < 1) map_h = map_height;
			if (map_w >512) map_w = 512;
			if (map_h >512) map_h = 512;
			map_width = map_w;
			map_height = map_h;
			//Reset_Map();
		}
	}
}

void mouse_drag(int x, int y){
	if (Grab_Map){
		sx1 = x/gui_scale;
		sy1 = y/gui_scale;
	}
	
	mouse_x=x; mouse_y=y;
}

void mouse_pos(int x,int y) {
    mouse_x=x; mouse_y=y;
}



////////////////////////
////////////////////////
int main( int argc, char *argv[] ){
	map_width = 40;
	map_height = 25;
	OpenGl_Init( argc, argv );
	Create_Quad_Arrays();
	
	// Initialize CHOOSECOLOR 
	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = hwnd;
	cc.lpCustColors = (LPDWORD) acrCustClr;
	cc.rgbResult = rgbCurrent;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	
	Reset_Map();
	
	if (argv[1]){
		char *name = argv[1];
		int size = strlen(name);
		char a = name[size-3]; char b = name[size-2]; char c = name[size-1];
		if ((a == 'm' || a == 'M') && (b == 'a' || b == 'A') && (c == 'p' || c == 'P')) {
			filename = name;
			Load_Map(0);
		}
	}
	map_w = map_width;
	map_h = map_height;
	//Display callback and enter event loop
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutPassiveMotionFunc(mouse_pos);
	glutMotionFunc(mouse_drag); 
	glutMouseFunc(mouse_click);
	glutSpecialFunc(SpecialKeys);
	glutKeyboardFunc(NormalKeys);
	glutReshapeFunc(resize);

	glutMainLoop();
	
	return 0;
}


