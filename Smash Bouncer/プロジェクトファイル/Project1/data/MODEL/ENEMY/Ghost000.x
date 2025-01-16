xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 267;
 -0.00375;22.36573;-0.02879;,
 -2.70973;21.49045;-2.73477;,
 -3.83057;21.49045;-0.02879;,
 -0.00375;22.36573;-0.02879;,
 -0.00375;21.49045;-3.85562;,
 -0.00375;22.36573;-0.02879;,
 2.70223;21.49045;-2.73477;,
 -0.00375;22.36573;-0.02879;,
 3.82308;21.49045;-0.02879;,
 -0.00375;22.36573;-0.02879;,
 2.70223;21.49045;2.67719;,
 -0.00375;22.36573;-0.02879;,
 -0.00375;21.49045;3.79804;,
 -0.00375;22.36573;-0.02879;,
 -2.70973;21.49045;2.67719;,
 -0.00375;22.36573;-0.02879;,
 -3.83057;21.49045;-0.02879;,
 -5.00375;18.99784;-5.02879;,
 -7.07482;18.99784;-0.02879;,
 -0.00375;18.99784;-7.09986;,
 4.99625;18.99784;-5.02879;,
 7.06733;18.99784;-0.02879;,
 4.99625;18.99784;4.97121;,
 -0.00375;18.99784;7.04228;,
 -5.00374;18.99784;4.97121;,
 -7.07482;18.99784;-0.02879;,
 -6.53656;15.26738;-6.56160;,
 -9.24254;15.26738;-0.02879;,
 -0.00375;15.26738;-9.26758;,
 6.52906;15.26738;-6.56160;,
 9.23505;15.26738;-0.02879;,
 6.52906;15.26738;6.50403;,
 -0.00375;15.26738;9.21000;,
 -6.53655;15.26738;6.50403;,
 -9.24254;15.26738;-0.02879;,
 -7.07481;10.86701;-7.09986;,
 -10.00374;10.86701;-0.02879;,
 -0.00375;10.86701;-10.03516;,
 7.06732;10.86701;-7.09986;,
 9.99625;10.86701;-0.02879;,
 7.06732;10.86701;7.04228;,
 -0.00375;10.86701;9.97122;,
 -7.07481;10.86701;7.04228;,
 -10.00374;10.86701;-0.02879;,
 -6.53656;4.25858;-3.63256;,
 -8.36549;6.32915;2.64718;,
 -0.00375;4.27031;-6.77525;,
 6.52907;4.25858;-3.63256;,
 8.62231;6.32915;2.64719;,
 5.85018;8.39971;8.92692;,
 -0.00374;11.45174;17.23200;,
 -5.85767;8.39971;8.92692;,
 -8.36549;6.32915;2.64718;,
 -5.00374;2.26456;-1.26489;,
 -5.76711;2.74321;3.54142;,
 -0.00375;1.60814;-3.25573;,
 4.99626;2.26456;-1.26489;,
 5.75962;2.74321;3.54142;,
 4.99626;4.32795;8.34772;,
 -0.00374;4.98437;11.01709;,
 -5.00375;4.32795;8.34772;,
 -5.76711;2.74321;3.54142;,
 -2.70973;0.59559;1.53777;,
 -3.83058;1.45325;4.13892;,
 -0.00375;0.24034;0.46033;,
 2.70223;0.59559;1.53777;,
 3.82309;1.45325;4.13892;,
 2.70224;2.31091;6.74008;,
 -0.00375;2.66616;7.81751;,
 -2.70973;2.31091;6.74008;,
 -3.83058;1.45325;4.13892;,
 -0.00375;0.61187;4.34874;,
 -0.00375;0.61187;4.34874;,
 -0.00375;0.61187;4.34874;,
 -0.00375;0.61187;4.34874;,
 -0.00375;0.61187;4.34874;,
 -0.00375;0.61187;4.34874;,
 -0.00375;0.61187;4.34874;,
 -0.00375;0.61187;4.34874;,
 -3.88275;16.16414;-7.65771;,
 -4.16508;16.01284;-8.14672;,
 -4.44743;16.01284;-7.65771;,
 -3.88275;16.16414;-7.65771;,
 -3.60042;16.01284;-8.14672;,
 -3.88275;16.16414;-7.65771;,
 -3.31808;16.01284;-7.65771;,
 -3.88275;16.16414;-7.65771;,
 -3.60042;16.01284;-7.16868;,
 -3.88275;16.16414;-7.65771;,
 -4.16508;16.01284;-7.16867;,
 -3.88275;16.16414;-7.65771;,
 -4.44743;16.01284;-7.65771;,
 -4.37178;15.59946;-8.50472;,
 -4.86079;15.59946;-7.65770;,
 -3.39373;15.59946;-8.50472;,
 -2.90471;15.59946;-7.65771;,
 -3.39373;15.59946;-6.81070;,
 -4.37178;15.59946;-6.81069;,
 -4.86079;15.59946;-7.65770;,
 -4.44742;15.03479;-8.63575;,
 -5.01210;15.03479;-7.65771;,
 -3.31808;15.03479;-8.63575;,
 -2.75341;15.03479;-7.65771;,
 -3.31807;15.03479;-6.67965;,
 -4.44743;15.03479;-6.67966;,
 -5.01210;15.03479;-7.65771;,
 -4.37178;14.47012;-8.50472;,
 -4.86079;14.47012;-7.65770;,
 -3.39373;14.47012;-8.50472;,
 -2.90471;14.47012;-7.65771;,
 -3.39373;14.47012;-6.81070;,
 -4.37178;14.47012;-6.81069;,
 -4.86079;14.47012;-7.65770;,
 -4.16508;14.05675;-8.14672;,
 -4.44743;14.05675;-7.65771;,
 -3.60042;14.05675;-8.14672;,
 -3.31808;14.05675;-7.65771;,
 -3.60042;14.05675;-7.16868;,
 -4.16508;14.05675;-7.16867;,
 -4.44743;14.05675;-7.65771;,
 -3.88275;13.90544;-7.65771;,
 -3.88275;13.90544;-7.65771;,
 -3.88275;13.90544;-7.65771;,
 -3.88275;13.90544;-7.65771;,
 -3.88275;13.90544;-7.65771;,
 -3.88275;13.90544;-7.65771;,
 3.80034;16.16414;-7.65771;,
 3.51801;16.01284;-8.14672;,
 3.23567;16.01284;-7.65771;,
 3.80034;16.16414;-7.65771;,
 4.08268;16.01284;-8.14673;,
 3.80034;16.16414;-7.65771;,
 4.36503;16.01284;-7.65770;,
 3.80034;16.16414;-7.65771;,
 4.08268;16.01284;-7.16868;,
 3.80034;16.16414;-7.65771;,
 3.51801;16.01284;-7.16867;,
 3.80034;16.16414;-7.65771;,
 3.23567;16.01284;-7.65771;,
 3.31134;15.59946;-8.50472;,
 2.82232;15.59946;-7.65771;,
 4.28937;15.59946;-8.50471;,
 4.77839;15.59946;-7.65771;,
 4.28937;15.59946;-6.81069;,
 3.31133;15.59946;-6.81069;,
 2.82232;15.59946;-7.65771;,
 3.23567;15.03479;-8.63575;,
 2.67100;15.03479;-7.65771;,
 4.36502;15.03479;-8.63575;,
 4.92970;15.03479;-7.65771;,
 4.36502;15.03479;-6.67965;,
 3.23567;15.03479;-6.67966;,
 2.67100;15.03479;-7.65771;,
 3.31134;14.47012;-8.50472;,
 2.82232;14.47012;-7.65771;,
 4.28937;14.47012;-8.50471;,
 4.77839;14.47012;-7.65771;,
 4.28937;14.47012;-6.81069;,
 3.31133;14.47012;-6.81069;,
 2.82232;14.47012;-7.65771;,
 3.51801;14.05675;-8.14672;,
 3.23567;14.05675;-7.65771;,
 4.08268;14.05675;-8.14673;,
 4.36503;14.05675;-7.65770;,
 4.08268;14.05675;-7.16868;,
 3.51801;14.05675;-7.16867;,
 3.23567;14.05675;-7.65771;,
 3.80034;13.90544;-7.65771;,
 3.80034;13.90544;-7.65771;,
 3.80034;13.90544;-7.65771;,
 3.80034;13.90544;-7.65771;,
 3.80034;13.90544;-7.65771;,
 3.80034;13.90544;-7.65771;,
 -6.71972;11.69881;-7.11327;,
 -7.00547;11.54974;-7.10563;,
 -7.09765;11.57541;-6.82521;,
 -6.71972;11.69881;-7.11327;,
 -6.61800;11.54728;-7.37901;,
 -6.71972;11.69881;-7.11327;,
 -6.32269;11.57049;-7.37200;,
 -6.71972;11.69881;-7.11327;,
 -6.41487;11.59616;-7.09159;,
 -6.71972;11.69881;-7.11327;,
 -6.80234;11.59862;-6.81819;,
 -6.71972;11.69881;-7.11327;,
 -7.09765;11.57541;-6.82521;,
 -7.19556;11.18889;-7.07071;,
 -7.35522;11.23336;-6.58502;,
 -6.52445;11.18462;-7.54426;,
 -6.01296;11.22483;-7.53210;,
 -6.17262;11.26930;-7.04640;,
 -6.84375;11.27356;-6.57286;,
 -7.35522;11.23336;-6.58502;,
 -7.23907;10.71297;-7.01788;,
 -7.42342;10.76432;-6.45705;,
 -6.46413;10.70804;-7.56467;,
 -5.87352;10.75446;-7.55064;,
 -6.05788;10.80581;-6.98981;,
 -6.83282;10.81074;-6.44301;,
 -7.42342;10.76432;-6.45705;,
 -7.12433;10.24948;-6.96128;,
 -7.28397;10.29395;-6.47558;,
 -6.45321;10.24521;-7.43483;,
 -5.94172;10.28542;-7.42267;,
 -6.10138;10.32989;-6.93697;,
 -6.77250;10.33415;-6.46343;,
 -7.28397;10.29395;-6.47558;,
 -6.88208;9.92261;-6.91609;,
 -6.97425;9.94829;-6.63568;,
 -6.49460;9.92015;-7.18948;,
 -6.19931;9.94336;-7.18246;,
 -6.29147;9.96904;-6.90204;,
 -6.67895;9.97150;-6.62866;,
 -6.97425;9.94829;-6.63568;,
 -6.57723;9.81997;-6.89441;,
 -6.57723;9.81997;-6.89441;,
 -6.57723;9.81997;-6.89441;,
 -6.57723;9.81997;-6.89441;,
 -6.57723;9.81997;-6.89441;,
 -6.57723;9.81997;-6.89441;,
 6.84319;11.68936;-7.03420;,
 6.76639;11.54332;-7.31116;,
 6.47126;11.56282;-7.32863;,
 6.84319;11.68936;-7.03420;,
 7.12934;11.54357;-7.00595;,
 6.84319;11.68936;-7.03420;,
 7.19717;11.56332;-6.71821;,
 6.84319;11.68936;-7.03420;,
 6.90203;11.58282;-6.73566;,
 6.84319;11.68936;-7.03420;,
 6.53908;11.58257;-7.04087;,
 6.84319;11.68936;-7.03420;,
 6.47126;11.56282;-7.32863;,
 6.69221;11.18383;-7.49234;,
 6.18102;11.21759;-7.52259;,
 7.32088;11.18427;-6.96371;,
 7.43834;11.21847;-6.46530;,
 6.92714;11.25224;-6.49556;,
 6.29849;11.25180;-7.02419;,
 6.18102;11.21759;-7.52259;,
 6.64053;10.70721;-7.52920;,
 6.05025;10.74621;-7.56412;,
 7.36644;10.70772;-6.91878;,
 7.50207;10.74722;-6.34329;,
 6.91180;10.78622;-6.37820;,
 6.18589;10.78571;-6.98862;,
 6.05025;10.74621;-7.56412;,
 6.62518;10.24118;-7.41185;,
 6.11398;10.27495;-7.44209;,
 7.25384;10.24162;-6.88322;,
 7.37130;10.27583;-6.38481;,
 6.86011;10.30960;-6.41506;,
 6.23146;10.30916;-6.94369;,
 6.11398;10.27495;-7.44209;,
 6.65029;9.91061;-7.17174;,
 6.35515;9.93010;-7.18920;,
 7.01324;9.91086;-6.86653;,
 7.08107;9.93061;-6.57878;,
 6.78593;9.95011;-6.59623;,
 6.42298;9.94985;-6.90144;,
 6.35515;9.93010;-7.18920;,
 6.70913;9.80406;-6.87320;,
 6.70913;9.80406;-6.87320;,
 6.70913;9.80406;-6.87320;,
 6.70913;9.80406;-6.87320;,
 6.70913;9.80406;-6.87320;,
 6.70913;9.80406;-6.87320;;
 
 208;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;2,1,17,18;,
 4;1,4,19,17;,
 4;4,6,20,19;,
 4;6,8,21,20;,
 4;8,10,22,21;,
 4;10,12,23,22;,
 4;12,14,24,23;,
 4;14,16,25,24;,
 4;18,17,26,27;,
 4;17,19,28,26;,
 4;19,20,29,28;,
 4;20,21,30,29;,
 4;21,22,31,30;,
 4;22,23,32,31;,
 4;23,24,33,32;,
 4;24,25,34,33;,
 4;27,26,35,36;,
 4;26,28,37,35;,
 4;28,29,38,37;,
 4;29,30,39,38;,
 4;30,31,40,39;,
 4;31,32,41,40;,
 4;32,33,42,41;,
 4;33,34,43,42;,
 4;36,35,44,45;,
 4;35,37,46,44;,
 4;37,38,47,46;,
 4;38,39,48,47;,
 4;39,40,49,48;,
 4;40,41,50,49;,
 4;41,42,51,50;,
 4;42,43,52,51;,
 4;45,44,53,54;,
 4;44,46,55,53;,
 4;46,47,56,55;,
 4;47,48,57,56;,
 4;48,49,58,57;,
 4;49,50,59,58;,
 4;50,51,60,59;,
 4;51,52,61,60;,
 4;54,53,62,63;,
 4;53,55,64,62;,
 4;55,56,65,64;,
 4;56,57,66,65;,
 4;57,58,67,66;,
 4;58,59,68,67;,
 4;59,60,69,68;,
 4;60,61,70,69;,
 3;63,62,71;,
 3;62,64,72;,
 3;64,65,73;,
 3;65,66,74;,
 3;66,67,75;,
 3;67,68,76;,
 3;68,69,77;,
 3;69,70,78;,
 3;79,80,81;,
 3;82,83,80;,
 3;84,85,83;,
 3;86,87,85;,
 3;88,89,87;,
 3;90,91,89;,
 4;81,80,92,93;,
 4;80,83,94,92;,
 4;83,85,95,94;,
 4;85,87,96,95;,
 4;87,89,97,96;,
 4;89,91,98,97;,
 4;93,92,99,100;,
 4;92,94,101,99;,
 4;94,95,102,101;,
 4;95,96,103,102;,
 4;96,97,104,103;,
 4;97,98,105,104;,
 4;100,99,106,107;,
 4;99,101,108,106;,
 4;101,102,109,108;,
 4;102,103,110,109;,
 4;103,104,111,110;,
 4;104,105,112,111;,
 4;107,106,113,114;,
 4;106,108,115,113;,
 4;108,109,116,115;,
 4;109,110,117,116;,
 4;110,111,118,117;,
 4;111,112,119,118;,
 3;114,113,120;,
 3;113,115,121;,
 3;115,116,122;,
 3;116,117,123;,
 3;117,118,124;,
 3;118,119,125;,
 3;126,127,128;,
 3;129,130,127;,
 3;131,132,130;,
 3;133,134,132;,
 3;135,136,134;,
 3;137,138,136;,
 4;128,127,139,140;,
 4;127,130,141,139;,
 4;130,132,142,141;,
 4;132,134,143,142;,
 4;134,136,144,143;,
 4;136,138,145,144;,
 4;140,139,146,147;,
 4;139,141,148,146;,
 4;141,142,149,148;,
 4;142,143,150,149;,
 4;143,144,151,150;,
 4;144,145,152,151;,
 4;147,146,153,154;,
 4;146,148,155,153;,
 4;148,149,156,155;,
 4;149,150,157,156;,
 4;150,151,158,157;,
 4;151,152,159,158;,
 4;154,153,160,161;,
 4;153,155,162,160;,
 4;155,156,163,162;,
 4;156,157,164,163;,
 4;157,158,165,164;,
 4;158,159,166,165;,
 3;161,160,167;,
 3;160,162,168;,
 3;162,163,169;,
 3;163,164,170;,
 3;164,165,171;,
 3;165,166,172;,
 3;173,174,175;,
 3;176,177,174;,
 3;178,179,177;,
 3;180,181,179;,
 3;182,183,181;,
 3;184,185,183;,
 4;175,174,186,187;,
 4;174,177,188,186;,
 4;177,179,189,188;,
 4;179,181,190,189;,
 4;181,183,191,190;,
 4;183,185,192,191;,
 4;187,186,193,194;,
 4;186,188,195,193;,
 4;188,189,196,195;,
 4;189,190,197,196;,
 4;190,191,198,197;,
 4;191,192,199,198;,
 4;194,193,200,201;,
 4;193,195,202,200;,
 4;195,196,203,202;,
 4;196,197,204,203;,
 4;197,198,205,204;,
 4;198,199,206,205;,
 4;201,200,207,208;,
 4;200,202,209,207;,
 4;202,203,210,209;,
 4;203,204,211,210;,
 4;204,205,212,211;,
 4;205,206,213,212;,
 3;208,207,214;,
 3;207,209,215;,
 3;209,210,216;,
 3;210,211,217;,
 3;211,212,218;,
 3;212,213,219;,
 3;220,221,222;,
 3;223,224,221;,
 3;225,226,224;,
 3;227,228,226;,
 3;229,230,228;,
 3;231,232,230;,
 4;222,221,233,234;,
 4;221,224,235,233;,
 4;224,226,236,235;,
 4;226,228,237,236;,
 4;228,230,238,237;,
 4;230,232,239,238;,
 4;234,233,240,241;,
 4;233,235,242,240;,
 4;235,236,243,242;,
 4;236,237,244,243;,
 4;237,238,245,244;,
 4;238,239,246,245;,
 4;241,240,247,248;,
 4;240,242,249,247;,
 4;242,243,250,249;,
 4;243,244,251,250;,
 4;244,245,252,251;,
 4;245,246,253,252;,
 4;248,247,254,255;,
 4;247,249,256,254;,
 4;249,250,257,256;,
 4;250,251,258,257;,
 4;251,252,259,258;,
 4;252,253,260,259;,
 3;255,254,261;,
 3;254,256,262;,
 3;256,257,263;,
 3;257,258,264;,
 3;258,259,265;,
 3;259,260,266;;
 
 MeshMaterialList {
  3;
  208;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.190000;0.190000;0.190000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.097600;0.295200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  210;
  0.000000;1.000000;-0.000000;,
  -0.423296;0.905992;0.000000;,
  -0.299315;0.905992;-0.299315;,
  0.000000;0.905991;-0.423296;,
  0.299315;0.905992;-0.299315;,
  0.423296;0.905992;-0.000000;,
  0.299315;0.905992;0.299315;,
  -0.000000;0.905992;0.423296;,
  -0.299315;0.905992;0.299315;,
  -0.749202;0.662342;-0.000000;,
  -0.529766;0.662341;-0.529766;,
  0.000000;0.662341;-0.749203;,
  0.529766;0.662341;-0.529766;,
  0.749202;0.662341;-0.000000;,
  0.529766;0.662342;0.529766;,
  -0.000000;0.662342;0.749202;,
  -0.529766;0.662342;0.529766;,
  -0.939255;0.343220;-0.000000;,
  -0.664191;0.343364;-0.664042;,
  0.000000;0.343559;-0.939131;,
  0.664191;0.343364;-0.664042;,
  0.939255;0.343220;-0.000000;,
  0.664154;0.343220;0.664154;,
  -0.000000;0.343220;0.939255;,
  -0.664154;0.343220;0.664153;,
  -0.998470;-0.039522;0.038670;,
  -0.729011;-0.129712;-0.672099;,
  0.000000;-0.157117;-0.987580;,
  0.725958;-0.125477;-0.676195;,
  0.999019;-0.025282;0.036356;,
  0.741261;0.293058;0.603862;,
  -0.000000;0.580539;0.814232;,
  -0.745663;0.283543;0.602984;,
  -0.914995;-0.384393;0.122582;,
  -0.652662;-0.603018;-0.458697;,
  0.000000;-0.670179;-0.742199;,
  0.645191;-0.605284;-0.466219;,
  0.913577;-0.386947;0.125093;,
  0.782217;-0.310600;0.540060;,
  -0.000000;0.880010;0.474956;,
  -0.414623;0.800803;0.432206;,
  -0.717739;-0.668734;0.194023;,
  -0.504146;-0.829706;-0.239633;,
  0.000000;-0.890142;-0.455683;,
  0.496953;-0.833696;-0.240808;,
  0.706428;-0.679774;0.197146;,
  0.544054;-0.610934;0.575122;,
  0.180019;-0.682602;0.708271;,
  -0.550984;-0.607822;0.571812;,
  -0.397563;-0.878585;0.264636;,
  -0.295602;-0.955307;-0.002911;,
  0.000000;-0.992141;-0.125129;,
  0.295602;-0.955307;-0.002911;,
  0.397563;-0.878585;0.264636;,
  0.262134;-0.830258;0.491891;,
  -0.000000;-0.819911;0.572491;,
  -0.262135;-0.830258;0.491891;,
  -0.000000;-0.950347;0.311193;,
  0.414623;0.800803;0.432206;,
  -0.788393;-0.316679;0.527400;,
  0.508775;-0.408155;0.757996;,
  -0.508775;-0.408155;0.757995;,
  0.000003;1.000000;-0.000003;,
  -0.492323;0.870413;-0.000002;,
  -0.246161;0.870412;-0.426366;,
  0.246161;0.870412;-0.426365;,
  0.492325;0.870412;-0.000002;,
  0.246166;0.870411;0.426365;,
  -0.246160;0.870412;0.426365;,
  -0.862097;0.506743;-0.000002;,
  -0.431049;0.506745;-0.746596;,
  0.431048;0.506745;-0.746597;,
  0.862096;0.506745;-0.000002;,
  0.431049;0.506746;0.746596;,
  -0.431049;0.506744;0.746597;,
  -1.000000;0.000000;-0.000002;,
  -0.500001;-0.000000;-0.866025;,
  0.500001;0.000000;-0.866025;,
  1.000000;0.000000;-0.000002;,
  0.500002;0.000000;0.866024;,
  -0.500004;0.000000;0.866023;,
  -0.862094;-0.506749;-0.000002;,
  -0.431047;-0.506752;-0.746593;,
  0.431046;-0.506751;-0.746594;,
  0.862092;-0.506751;-0.000002;,
  0.431047;-0.506753;0.746592;,
  -0.431047;-0.506750;0.746594;,
  -0.492326;-0.870411;-0.000002;,
  -0.246163;-0.870410;-0.426368;,
  0.246163;-0.870411;-0.426368;,
  0.492327;-0.870410;-0.000002;,
  0.246167;-0.870410;0.426367;,
  -0.246161;-0.870411;0.426367;,
  0.000003;-1.000000;-0.000003;,
  -0.000002;1.000000;-0.000004;,
  -0.492331;0.870408;-0.000004;,
  -0.246164;0.870409;-0.426370;,
  0.246161;0.870412;-0.426367;,
  0.492322;0.870413;-0.000001;,
  0.246162;0.870411;0.426366;,
  -0.246165;0.870410;0.426367;,
  -0.862097;0.506743;-0.000003;,
  -0.431048;0.506743;-0.746598;,
  0.431048;0.506743;-0.746598;,
  0.862097;0.506743;-0.000002;,
  0.431049;0.506743;0.746598;,
  -0.431050;0.506744;0.746597;,
  -1.000000;0.000000;-0.000001;,
  -0.499999;0.000000;-0.866026;,
  0.500000;0.000000;-0.866025;,
  1.000000;0.000000;-0.000003;,
  0.500002;0.000000;0.866024;,
  -0.500003;-0.000000;0.866024;,
  -0.862093;-0.506749;-0.000003;,
  -0.431047;-0.506750;-0.746595;,
  0.431046;-0.506750;-0.746595;,
  0.862094;-0.506749;-0.000002;,
  0.431047;-0.506749;0.746595;,
  -0.431049;-0.506750;0.746593;,
  -0.492333;-0.870407;-0.000004;,
  -0.246166;-0.870408;-0.426372;,
  0.246162;-0.870410;-0.426369;,
  0.492325;-0.870411;-0.000001;,
  0.246164;-0.870410;0.426369;,
  -0.246167;-0.870409;0.426369;,
  -0.000002;-1.000000;-0.000004;,
  -0.075116;0.990478;-0.115372;,
  -0.526341;0.845116;-0.093510;,
  -0.611047;0.600527;-0.515741;,
  -0.275965;0.598400;-0.752171;,
  0.095494;0.841168;-0.532275;,
  0.505861;0.786553;0.354173;,
  0.170773;0.788681;0.590610;,
  -0.915790;0.238876;-0.322903;,
  -0.781988;0.173061;-0.598787;,
  -0.300534;0.170002;-0.938498;,
  0.004788;0.233028;-0.972458;,
  0.737035;0.419705;0.529742;,
  0.255575;0.422766;0.869454;,
  -0.947407;-0.106981;-0.301620;,
  -0.799778;-0.128945;-0.586283;,
  -0.285357;-0.132218;-0.949257;,
  0.032497;-0.113215;-0.993039;,
  0.799773;0.128948;0.586290;,
  0.285353;0.132218;0.949259;,
  -0.864322;-0.439885;-0.243821;,
  -0.737040;-0.419708;-0.529734;,
  -0.255576;-0.422770;-0.869452;,
  0.056270;-0.445743;-0.893390;,
  0.781989;-0.173054;0.598787;,
  0.300528;-0.169991;0.938502;,
  -0.393026;-0.912770;0.111271;,
  -0.505850;-0.786569;-0.354154;,
  -0.170762;-0.788695;-0.590594;,
  0.228808;-0.916726;-0.327507;,
  0.611047;-0.600529;0.515738;,
  0.275956;-0.598395;0.752178;,
  0.075117;-0.990477;0.115384;,
  0.773897;0.601119;0.199350;,
  0.864316;0.439888;0.243837;,
  -0.066505;0.606461;0.792327;,
  -0.056273;0.445740;0.893392;,
  0.947404;0.106983;0.301631;,
  -0.032502;0.113213;0.993039;,
  0.915792;-0.238883;0.322893;,
  -0.004796;-0.233027;0.972458;,
  0.851152;-0.417631;0.318000;,
  0.010754;-0.412283;0.910992;,
  0.070690;0.993881;-0.084876;,
  -0.062038;0.853018;-0.518181;,
  0.330020;0.620285;-0.711571;,
  0.643894;0.620511;-0.447624;,
  0.520444;0.853424;-0.028367;,
  -0.231027;0.771569;0.592712;,
  -0.544915;0.771347;0.328772;,
  0.073994;0.257211;-0.963518;,
  0.376219;0.197010;-0.905343;,
  0.827210;0.197334;-0.526102;,
  0.936323;0.257829;-0.238378;,
  -0.333919;0.397797;0.854550;,
  -0.784914;0.397478;0.475312;,
  0.052982;-0.088707;-0.994648;,
  0.366244;-0.104997;-0.924576;,
  0.848116;-0.104662;-0.519369;,
  0.970883;-0.088068;-0.222779;,
  -0.366245;0.105001;0.924575;,
  -0.848115;0.104664;0.519371;,
  0.025559;-0.423890;-0.905353;,
  0.333919;-0.397798;-0.854549;,
  0.784913;-0.397488;-0.475306;,
  0.887889;-0.423294;-0.180207;,
  -0.376221;-0.197010;0.905342;,
  -0.827209;-0.197324;0.526107;,
  -0.187478;-0.910911;-0.367551;,
  0.231043;-0.771558;-0.592720;,
  0.544921;-0.771344;-0.328770;,
  0.395008;-0.910503;0.122281;,
  -0.330017;-0.620276;0.711580;,
  -0.643895;-0.620499;0.447639;,
  -0.070672;-0.993882;0.084877;,
  -0.009086;0.587205;0.809387;,
  -0.025553;0.423891;0.905353;,
  -0.796308;0.586652;0.147424;,
  -0.887892;0.423282;0.180220;,
  -0.052981;0.088709;0.994648;,
  -0.970881;0.088067;0.222787;,
  -0.073997;-0.257213;0.963517;,
  -0.936324;-0.257813;0.238391;,
  -0.081795;-0.435045;0.896686;,
  -0.868996;-0.435599;0.234731;;
  208;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;9,10,18,17;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;17,18,26,25;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  4;25,26,34,33;,
  4;26,27,35,34;,
  4;27,28,36,35;,
  4;28,29,37,36;,
  4;29,30,38,37;,
  4;30,31,39,58;,
  4;31,32,40,39;,
  4;32,25,33,59;,
  4;33,34,42,41;,
  4;34,35,43,42;,
  4;35,36,44,43;,
  4;36,37,45,44;,
  4;37,38,46,45;,
  4;38,60,47,46;,
  4;61,59,48,61;,
  4;59,33,41,48;,
  4;41,42,50,49;,
  4;42,43,51,50;,
  4;43,44,52,51;,
  4;44,45,53,52;,
  4;45,46,54,53;,
  4;46,47,55,54;,
  4;47,48,56,55;,
  4;48,41,49,56;,
  3;49,50,57;,
  3;50,51,57;,
  3;51,52,57;,
  3;52,53,57;,
  3;53,54,57;,
  3;54,55,57;,
  3;55,56,57;,
  3;56,49,57;,
  3;62,64,63;,
  3;62,65,64;,
  3;62,66,65;,
  3;62,67,66;,
  3;62,68,67;,
  3;62,63,68;,
  4;63,64,70,69;,
  4;64,65,71,70;,
  4;65,66,72,71;,
  4;66,67,73,72;,
  4;67,68,74,73;,
  4;68,63,69,74;,
  4;69,70,76,75;,
  4;70,71,77,76;,
  4;71,72,78,77;,
  4;72,73,79,78;,
  4;73,74,80,79;,
  4;74,69,75,80;,
  4;75,76,82,81;,
  4;76,77,83,82;,
  4;77,78,84,83;,
  4;78,79,85,84;,
  4;79,80,86,85;,
  4;80,75,81,86;,
  4;81,82,88,87;,
  4;82,83,89,88;,
  4;83,84,90,89;,
  4;84,85,91,90;,
  4;85,86,92,91;,
  4;86,81,87,92;,
  3;87,88,93;,
  3;88,89,93;,
  3;89,90,93;,
  3;90,91,93;,
  3;91,92,93;,
  3;92,87,93;,
  3;94,96,95;,
  3;94,97,96;,
  3;94,98,97;,
  3;94,99,98;,
  3;94,100,99;,
  3;94,95,100;,
  4;95,96,102,101;,
  4;96,97,103,102;,
  4;97,98,104,103;,
  4;98,99,105,104;,
  4;99,100,106,105;,
  4;100,95,101,106;,
  4;101,102,108,107;,
  4;102,103,109,108;,
  4;103,104,110,109;,
  4;104,105,111,110;,
  4;105,106,112,111;,
  4;106,101,107,112;,
  4;107,108,114,113;,
  4;108,109,115,114;,
  4;109,110,116,115;,
  4;110,111,117,116;,
  4;111,112,118,117;,
  4;112,107,113,118;,
  4;113,114,120,119;,
  4;114,115,121,120;,
  4;115,116,122,121;,
  4;116,117,123,122;,
  4;117,118,124,123;,
  4;118,113,119,124;,
  3;119,120,125;,
  3;120,121,125;,
  3;121,122,125;,
  3;122,123,125;,
  3;123,124,125;,
  3;124,119,125;,
  3;126,128,127;,
  3;126,129,128;,
  3;126,130,129;,
  3;126,131,130;,
  3;126,132,131;,
  3;126,127,132;,
  4;127,128,134,133;,
  4;128,129,135,134;,
  4;129,130,136,135;,
  4;158,131,137,159;,
  4;131,132,138,137;,
  4;132,160,161,138;,
  4;133,134,140,139;,
  4;134,135,141,140;,
  4;135,136,142,141;,
  4;159,137,143,162;,
  4;137,138,144,143;,
  4;138,161,163,144;,
  4;139,140,146,145;,
  4;140,141,147,146;,
  4;141,142,148,147;,
  4;162,143,149,164;,
  4;143,144,150,149;,
  4;144,163,165,150;,
  4;145,146,152,151;,
  4;146,147,153,152;,
  4;147,148,154,153;,
  4;164,149,155,166;,
  4;149,150,156,155;,
  4;150,165,167,156;,
  3;151,152,157;,
  3;152,153,157;,
  3;153,154,157;,
  3;154,155,157;,
  3;155,156,157;,
  3;156,151,157;,
  3;168,170,169;,
  3;168,171,170;,
  3;168,172,171;,
  3;168,173,172;,
  3;168,174,173;,
  3;168,169,174;,
  4;169,170,176,175;,
  4;170,171,177,176;,
  4;171,172,178,177;,
  4;200,173,179,201;,
  4;173,174,180,179;,
  4;174,202,203,180;,
  4;175,176,182,181;,
  4;176,177,183,182;,
  4;177,178,184,183;,
  4;201,179,185,204;,
  4;179,180,186,185;,
  4;180,203,205,186;,
  4;181,182,188,187;,
  4;182,183,189,188;,
  4;183,184,190,189;,
  4;204,185,191,206;,
  4;185,186,192,191;,
  4;186,205,207,192;,
  4;187,188,194,193;,
  4;188,189,195,194;,
  4;189,190,196,195;,
  4;206,191,197,208;,
  4;191,192,198,197;,
  4;192,207,209,198;,
  3;193,194,199;,
  3;194,195,199;,
  3;195,196,199;,
  3;196,197,199;,
  3;197,198,199;,
  3;198,193,199;;
 }
 MeshTextureCoords {
  267;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.125000;0.375000;,
  0.000000;0.375000;,
  0.250000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.125000;0.500000;,
  0.000000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.125000;0.625000;,
  0.000000;0.625000;,
  0.250000;0.625000;,
  0.375000;0.625000;,
  0.500000;0.625000;,
  0.625000;0.625000;,
  0.750000;0.625000;,
  0.875000;0.625000;,
  1.000000;0.625000;,
  0.125000;0.750000;,
  0.000000;0.750000;,
  0.250000;0.750000;,
  0.375000;0.750000;,
  0.500000;0.750000;,
  0.625000;0.750000;,
  0.750000;0.750000;,
  0.875000;0.750000;,
  1.000000;0.750000;,
  0.125000;0.875000;,
  0.000000;0.875000;,
  0.250000;0.875000;,
  0.375000;0.875000;,
  0.500000;0.875000;,
  0.625000;0.875000;,
  0.750000;0.875000;,
  0.875000;0.875000;,
  1.000000;0.875000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.083330;0.000000;,
  0.166670;0.166670;,
  0.000000;0.166670;,
  0.250000;0.000000;,
  0.333330;0.166670;,
  0.416670;0.000000;,
  0.500000;0.166670;,
  0.583330;0.000000;,
  0.666670;0.166670;,
  0.750000;0.000000;,
  0.833330;0.166670;,
  0.916670;0.000000;,
  1.000000;0.166670;,
  0.166670;0.333330;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.500000;0.666670;,
  0.666670;0.666670;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.083330;0.000000;,
  0.166670;0.166670;,
  0.000000;0.166670;,
  0.250000;0.000000;,
  0.333330;0.166670;,
  0.416670;0.000000;,
  0.500000;0.166670;,
  0.583330;0.000000;,
  0.666670;0.166670;,
  0.750000;0.000000;,
  0.833330;0.166670;,
  0.916670;0.000000;,
  1.000000;0.166670;,
  0.166670;0.333330;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.500000;0.666670;,
  0.666670;0.666670;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.083330;0.000000;,
  0.166670;0.166670;,
  0.000000;0.166670;,
  0.250000;0.000000;,
  0.333330;0.166670;,
  0.416670;0.000000;,
  0.500000;0.166670;,
  0.583330;0.000000;,
  0.666670;0.166670;,
  0.750000;0.000000;,
  0.833330;0.166670;,
  0.916670;0.000000;,
  1.000000;0.166670;,
  0.166670;0.333330;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.500000;0.666670;,
  0.666670;0.666670;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;,
  0.083330;0.000000;,
  0.166670;0.166670;,
  0.000000;0.166670;,
  0.250000;0.000000;,
  0.333330;0.166670;,
  0.416670;0.000000;,
  0.500000;0.166670;,
  0.583330;0.000000;,
  0.666670;0.166670;,
  0.750000;0.000000;,
  0.833330;0.166670;,
  0.916670;0.000000;,
  1.000000;0.166670;,
  0.166670;0.333330;,
  0.000000;0.333330;,
  0.333330;0.333330;,
  0.500000;0.333330;,
  0.666670;0.333330;,
  0.833330;0.333330;,
  1.000000;0.333330;,
  0.166670;0.500000;,
  0.000000;0.500000;,
  0.333330;0.500000;,
  0.500000;0.500000;,
  0.666670;0.500000;,
  0.833330;0.500000;,
  1.000000;0.500000;,
  0.166670;0.666670;,
  0.000000;0.666670;,
  0.333330;0.666670;,
  0.500000;0.666670;,
  0.666670;0.666670;,
  0.833330;0.666670;,
  1.000000;0.666670;,
  0.166670;0.833330;,
  0.000000;0.833330;,
  0.333330;0.833330;,
  0.500000;0.833330;,
  0.666670;0.833330;,
  0.833330;0.833330;,
  1.000000;0.833330;,
  0.083330;1.000000;,
  0.250000;1.000000;,
  0.416670;1.000000;,
  0.583330;1.000000;,
  0.750000;1.000000;,
  0.916670;1.000000;;
 }
}
