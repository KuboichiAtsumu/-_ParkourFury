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
 44;
 -0.07422;-0.01124;-0.32658;,
 0.68811;-0.23554;-2.25635;,
 -0.07422;-0.23554;-2.74611;,
 -0.07422;-0.01124;-0.32658;,
 1.00388;-0.23554;-0.32658;,
 -0.07422;-0.01124;-0.32658;,
 0.68811;-0.23554;0.85580;,
 -0.07422;-0.01124;-0.32658;,
 -0.07422;-0.23554;1.34556;,
 -0.07422;-0.01124;-0.32658;,
 -0.83655;-0.23554;0.85580;,
 -0.07422;-0.01124;-0.32658;,
 -1.15232;-0.23554;-0.32658;,
 -0.07422;-0.01124;-0.32658;,
 -0.83655;-0.23554;-2.25635;,
 -0.07422;-0.01124;-0.32658;,
 -0.07422;-0.23554;-2.74611;,
 1.33439;-0.87426;-3.25873;,
 -0.07422;-0.87426;-4.16369;,
 1.91785;-0.87426;-0.32658;,
 1.33439;-0.87426;1.09288;,
 -0.07422;-0.87426;2.17037;,
 -1.48283;-0.87426;1.09288;,
 -2.06629;-0.87426;-0.32658;,
 -1.48283;-0.87426;-3.25873;,
 -0.07422;-0.87426;-4.16369;,
 1.76622;-1.83019;-3.92848;,
 -0.07422;-1.83019;-5.11087;,
 2.22343;-1.83019;-0.32658;,
 1.76622;-1.83019;1.76266;,
 -0.07422;-1.83019;2.53841;,
 -1.91465;-1.83019;1.76266;,
 -2.37187;-1.83019;-0.32658;,
 -1.91465;-1.83019;-3.92848;,
 -0.07422;-1.83019;-5.11087;,
 1.91785;-2.95779;-4.16369;,
 -0.07422;-2.95779;-5.44347;,
 2.41274;-2.95779;-0.32658;,
 1.91785;-2.95779;1.99785;,
 -0.07422;-2.95779;2.87102;,
 -2.06629;-2.95779;1.99785;,
 -2.56118;-2.95779;-0.32658;,
 -2.06629;-2.95779;-4.16368;,
 -0.07422;-2.95779;-5.44347;;
 
 35;
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
 4;43,35,37,38;,
 4;43,38,39,40;,
 4;43,40,41,42;;
 
 MeshMaterialList {
  5;
  35;
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
  0;;
  Material {
   0.109804;0.109804;0.109804;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.232157;0.520784;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.290196;0.650980;1.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;1.000000;1.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   0.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  35;
  -0.000000;0.999879;0.015573;,
  -0.000000;0.967608;-0.252459;,
  0.284699;0.944760;-0.162403;,
  0.413125;0.910167;0.030390;,
  0.343533;0.903884;0.254910;,
  -0.000000;0.921795;0.387677;,
  -0.343534;0.903884;0.254910;,
  -0.413125;0.910167;0.030390;,
  -0.284699;0.944760;-0.162403;,
  -0.000000;0.824761;-0.565481;,
  0.583941;0.732250;-0.350461;,
  0.782353;0.620029;0.059057;,
  0.613121;0.627080;0.480472;,
  -0.000000;0.669238;0.743048;,
  -0.613122;0.627080;0.480471;,
  -0.782354;0.620028;0.059056;,
  -0.583942;0.732250;-0.350461;,
  -0.000000;0.516004;-0.856586;,
  0.782523;0.395704;-0.480704;,
  0.956500;0.286670;0.054104;,
  0.726303;0.360803;0.585069;,
  -0.000000;0.413130;0.910672;,
  -0.726303;0.360803;0.585068;,
  -0.956500;0.286671;0.054104;,
  -0.782524;0.395704;-0.480703;,
  0.524598;0.240865;-0.816567;,
  0.826508;0.220998;-0.517729;,
  0.985153;0.166464;0.041982;,
  0.753651;0.233027;0.614580;,
  -0.000000;0.269649;0.962959;,
  -0.753651;0.233027;0.614579;,
  -0.985153;0.166465;0.041981;,
  -0.826509;0.220998;-0.517729;,
  -0.524599;0.240864;-0.816566;,
  0.000000;-1.000000;-0.000000;;
  35;
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
  4;24,17,33,32;,
  4;34,34,34,34;,
  4;34,34,34,34;,
  4;34,34,34,34;;
 }
 MeshTextureCoords {
  44;
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
  1.000000;0.500000;;
 }
}
