#include "AssignmentScene2.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <iostream>

AssignmentScene2::AssignmentScene2() {}

AssignmentScene2::~AssignmentScene2() {}

double inline __declspec (naked) __fastcall sqrT(double n) {
	_asm fld qword ptr[esp + 4]
		_asm fsqrt
	_asm ret 8
}

void AssignmentScene2::Init() {
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");

	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	Mesh::SetMaterialLoc(m_parameters[U_MATERIAL_AMBIENT], 
		m_parameters[U_MATERIAL_DIFFUSE], 
		m_parameters[U_MATERIAL_SPECULAR], 
		m_parameters[U_MATERIAL_SHININESS]);
	glUseProgram(m_programID);

	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(15, 35, 15);
	light[0].color = WHITE;
	light[0].power = 0.7f;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;
	light[0].cosCutoff = cos(Math::DegreeToRadian(45));
	light[0].cosInner = cos(Math::DegreeToRadian(30));
	light[0].exponent = 3.f;
	light[0].spotDirection.Set(0.f, 1.f, 0.f);
	lighton = true;

	glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], light[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);
	glUniform1i(m_parameters[U_NUMLIGHTS], 1);
	
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	meshList[GEO_CYL] = MeshBuilder::GenerateCylinder("cyl", BROWN, 30, 0.1f, 3);

	meshList[GEO_CONE] = MeshBuilder::GenerateCone("cone", PURPLE, 30, 1, 5);
	
	meshList[GEO_SPHERE2] = MeshBuilder::GenerateSphere("dot", BLACK, 30, 30, 1);

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("body", WHITE, 30, 30, 1);

	meshList[GEO_CASTLEROOF] = MeshBuilder::GenerateCone("roof", GRAY, 30, 2, 1);

	meshList[GEO_CASTLEWALL] = MeshBuilder::GenerateQuad("wall", GRAY, 10, 2);
	meshList[GEO_CASTLEWALL]->textureID = LoadTGA("Image//ground.tga");

	meshList[GEO_CASTLEPILLAR] = MeshBuilder::GenerateCylinder("pillar", GRAY, 30, 1, 2);

	meshList[GEO_SUN] = MeshBuilder::GenerateSphere("sun", YELLOW, 30, 30, 5);
	meshList[GEO_SUN]->textureID = LoadTGA("Image//sun.tga");

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", WHITE, 1.f, 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//front-space.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", WHITE, 1.f, 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//back-space.tga");

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", WHITE, 1.f, 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//right-space.tga");

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", WHITE, 1.f, 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//left-space.tga");

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", WHITE, 1.f, 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//top-space.tga");

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", WHITE, 1.f, 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottom-space.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

	meshList[GEO_GROUND] = MeshBuilder::GenerateGround("ground", WHITE, 1.f, 1.f);
	meshList[GEO_GROUND]->textureID = LoadTGA("Image//concrete.tga");

	meshList[GEO_HOUSE1] = MeshBuilder::GenerateOBJMTL("cottage", "OBJ//cottage_obj.obj", "OBJ//cottage_obj.mtl");
	meshList[GEO_HOUSE1]->textureID = LoadTGA("Image//cottage_diffuse.tga");

	meshList[GEO_HOUSE2] = MeshBuilder::GenerateOBJMTL("house", "OBJ//house_type02.obj", "OBJ//house_type02.mtl");

	meshList[GEO_TREE] = MeshBuilder::GenerateOBJMTL("tree", "OBJ//tree_large.obj", "OBJ//tree_large.mtl");

	meshList[GEO_TREETOP] = MeshBuilder::GenerateCone("treetop", GREEN, 30, 1, 2);
	meshList[GEO_TREEBARK] = MeshBuilder::GenerateCylinder("treebark", BROWN, 30, 0.2f, 3);

	meshList[GEO_GLOCK] = MeshBuilder::GenerateOBJMTL("glock", "OBJ/blasterF.obj", "OBJ/blasterF.mtl");

	bounds = 300.f;

	Reset();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void AssignmentScene2::Update(double dt) {
	Mouse mouse;
	this->Update(dt, mouse);
}

void AssignmentScene2::Update(double dt, Mouse mouse) {
	if (Application::IsKeyPressed('1')) {
		glEnable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed('2')) {
		glDisable(GL_CULL_FACE);
	}
	if (Application::IsKeyPressed('3')) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (Application::IsKeyPressed('4')) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if (Application::IsKeyPressed('5')) {
		light[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	if (Application::IsKeyPressed('6')) {
		light[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	if (Application::IsKeyPressed('7')) {
		light[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
	}
	if (Application::IsKeyPressed('0')) {
		lighton = false;
	}
	if (Application::IsKeyPressed('9')) {
		lighton = true;
	}

	if (Application::IsKeyPressed('R')) {
		Reset();
	}
	float fps = (1.f / dt);
	if (Application::IsKeyPressed('C')) {
		dt *= 5.0f;
	}

	//unsigned LSPEED = 10.f;
	camera.Update(dt, mouse);

	if (camera.position.y > 0.4f) {
		camera.position.y -= (2.f * dt);
		if (camera.position.y < 0.30) {
			camera.position.y = 0.4f;
			//camera.target.y += 0.1f;
		}
		camera.target.y -= (2.f * dt);
	}
	if (camera.position.y < 0.30) {
		camera.position.y = 0.4f;
		//camera.target.y += 0.1f;
	}

	Mtx44 projection;
	projection.SetToPerspective(camera.fov, 40.0f / 30.0f, 0.1f, bounds);
	projectionStack.LoadMatrix(projection);

	Render();

	std::string fpsString = std::to_string(fps).substr(0, std::to_string(fps).find('.') + 4);
	RenderTextOnScreen(meshList[GEO_TEXT], ("FPS: " + fpsString), Color(0, 1, 0), 4, 0, 14);

	/*modelStack.PushMatrix();
	RenderImageOnScreen(meshList[GEO_CROSSHAIR], 4, 10, 7.5);
	modelStack.PopMatrix();*/
}

void AssignmentScene2::RenderMesh(Mesh* mesh, bool enableLight) {
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight && lighton) {
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	} else {
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	if (mesh->textureID > 0) {
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else {
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if (mesh->textureID > 0) {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void AssignmentScene2::RenderText(Mesh* mesh, std::string text, Color color) {
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i) {
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.7f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void AssignmentScene2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y) {
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i) {
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(0.5f + i, 0.5f, 0);
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void AssignmentScene2::RenderFacingText(Mesh* mesh, std::string text, Color color, float size, float x, float y, float z) {
	modelStack.PushMatrix();
	float middle = x - (text.length() / 2)* 0.4f;
	Vector3 origin = Vector3(0, 0, 1);
	Vector3 pos = Vector3(middle, 0, z);
	Vector3 lookAt = (camera.position - pos).Normalized();
	lookAt.y = 0;
	Mtx44 rotation;
	double uv = (origin.x * lookAt.x + origin.z * lookAt.z) / ((sqrT(origin.x * origin.x + origin.z * origin.z)) * sqrT(lookAt.x * lookAt.x + lookAt.z * lookAt.z));
	double angle = Math::RadianToDegree(acos(uv));
	if (angle >= 180)
		angle = 360 - angle;
	modelStack.Rotate(angle, 0, 1, 0);
	modelStack.Translate(middle, y, z);
	modelStack.Scale(size, size, size);
	RenderText(mesh, text, color);
	modelStack.PopMatrix();
}

void AssignmentScene2::RenderImageOnScreen(Mesh* mesh, float size, float x, float y) {
	if (!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);

	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	mesh->Render();
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void AssignmentScene2::RenderGun() {
	modelStack.PushMatrix();
	//Vector3 origin = Vector3(0, 0, 1);
	//Vector3 lookAt = (camera.target - camera.position).Normalized();
	//Vector3 cameraRight = lookAt.Cross(camera.up).Normalized();
	//double uv = (cameraRight.x * lookAt.x + cameraRight.z * lookAt.z) / ((sqrT(cameraRight.x * cameraRight.x + cameraRight.z * cameraRight.z)) * sqrT(lookAt.x * lookAt.x + lookAt.z * lookAt.z));
	//double angle = Math::RadianToDegree(acos(uv));
	//if (angle >= 180)
	//	angle = 360 - angle;
	objects[GEO_GLOCK].translate = camera.target;
	modelStack.Translate(objects[GEO_GLOCK].translate.x, objects[GEO_GLOCK].translate.y-0.4, objects[GEO_GLOCK].translate.z);
	modelStack.Rotate(45, 0, 1, 0);
	RenderMesh(meshList[GEO_GLOCK], false);
	modelStack.PopMatrix();
}

void AssignmentScene2::RenderSkybox() {
	float translate = 40;
	float scaleVal = (translate * 2) + (translate * 0.01f);
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y+translate, camera.position.z);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Rotate(270, 0, 0, 1);
	modelStack.Scale(scaleVal, scaleVal, scaleVal);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y-translate, camera.position.z);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(scaleVal, scaleVal, scaleVal);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y-0.4, camera.position.z-translate);
	modelStack.Scale(scaleVal, scaleVal, scaleVal);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y-0.4, camera.position.z+translate);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(scaleVal, scaleVal, scaleVal);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x+translate, camera.position.y-0.4, camera.position.z);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(scaleVal, scaleVal, scaleVal);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x-translate, camera.position.y-0.4, camera.position.z);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(scaleVal, scaleVal, scaleVal);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//modelStack.Translate(0, -0.4, 0);
	modelStack.Scale(scaleVal*scaleVal, scaleVal*scaleVal, scaleVal*scaleVal);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(meshList[GEO_GROUND], true);
	modelStack.PopMatrix();

	light[0].position.x = camera.position.x;
	light[0].position.z = camera.position.z;

	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);

	objects[GEO_SUN].rotate += 0.5f;
	if (objects[GEO_SUN].rotate >= 360.f) objects[GEO_SUN] = 0.f;
	modelStack.Rotate(objects[GEO_SUN].rotate, 0, 1, 0);
	modelStack.Scale(0.5, 0.5, 0.5);
	RenderMesh(meshList[GEO_SUN], false);
	modelStack.PopMatrix();
}

void AssignmentScene2::RenderA01Character(float x, float y, float z, float size, float rotate) {
	// Bottom body
	body.translate.x = x;
	body.translate.y = y;
	body.translate.z = z;
	body.scale = size;

	modelStack.PushMatrix();
	modelStack.Rotate(rotate, 0, 1, 0);
	modelStack.Translate(body.translate.x, body.translate.y, body.translate.z);
	modelStack.Scale(body.scale, body.scale, body.scale);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();

	// Middle body
	middle.scale = (body.scale * 0.6f);
	middle.translate.x = body.translate.x;
	middle.translate.z = body.translate.z;
	middle.translate.y = body.translate.y + (1 * body.scale) + (middle.scale*0.6f);
	modelStack.PushMatrix();
	modelStack.Rotate(rotate, 0, 1, 0);
	modelStack.Translate(middle.translate.x, middle.translate.y, middle.translate.z);
	modelStack.Scale(middle.scale, middle.scale, middle.scale);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();

	// Head
	head.translate.x = body.translate.x;
	head.translate.z = body.translate.z;
	head.scale = (middle.scale * 0.6f);
	head.translate.y = middle.translate.y + (1 * middle.scale) + (head.scale*0.6f);
	head.rotate = rotate;
	modelStack.PushMatrix();
	modelStack.Rotate(rotate, 0, 1, 0);
	modelStack.Translate(head.translate.x, head.translate.y, head.translate.z);
	//modelStack.Rotate(head.rotate, 1, 0, 0);
	modelStack.Scale(head.scale, head.scale, head.scale);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();

	// Eyes
	lefteye.scale = head.scale * 0.1f;
	modelStack.PushMatrix();
	modelStack.Rotate(rotate, 0, 1, 0);
	//modelStack.Translate(body.translate.x, body.translate.y, body.translate.z);
	modelStack.Translate(head.translate.x + (head.scale * 0.65f), head.translate.y + (head.scale*0.7f), head.translate.z - (head.scale * 0.3f));
	modelStack.Rotate(head.rotate, 1, 0, 0);
	modelStack.Scale(lefteye.scale, lefteye.scale, lefteye.scale);
	RenderMesh(meshList[GEO_SPHERE2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(rotate, 0, 1, 0);
	//modelStack.Translate(body.translate.x, body.translate.y, body.translate.z);
	modelStack.Translate(head.translate.x + (head.scale * 0.65f), head.translate.y + (head.scale * 0.7f), head.translate.z + (head.scale * 0.3f));
	modelStack.Rotate(head.rotate, 1, 0, 0);
	modelStack.Scale(lefteye.scale, lefteye.scale, lefteye.scale);
	RenderMesh(meshList[GEO_SPHERE2], true);
	modelStack.PopMatrix();

	// Body dots
	lefteye.scale *= 2.f;
	modelStack.PushMatrix();
	modelStack.Rotate(rotate, 0, 1, 0);
	//modelStack.Translate(body.translate.x, body.translate.y, body.translate.z);
	modelStack.Translate(middle.translate.x + middle.scale, middle.translate.y, middle.translate.z);
	modelStack.Scale(lefteye.scale, lefteye.scale, lefteye.scale);
	RenderMesh(meshList[GEO_SPHERE2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(rotate, 0, 1, 0);
	//modelStack.Translate(body.translate.x, body.translate.y, body.translate.z);
	modelStack.Translate(body.translate.x + body.scale, body.translate.y, body.translate.z);
	modelStack.Scale(lefteye.scale, lefteye.scale, lefteye.scale);
	RenderMesh(meshList[GEO_SPHERE2], true);
	modelStack.PopMatrix();

	// Nose
	nose.scale = head.scale * 0.5f;
	modelStack.PushMatrix();
	modelStack.Rotate(rotate, 0, 1, 0);
	//modelStack.Translate(body.translate.x, body.translate.y, body.translate.z);
	modelStack.Translate(head.translate.x + head.scale, head.translate.y, head.translate.z);
	modelStack.Rotate(nose.rotate, 0, 0, 1);
	modelStack.Scale(nose.scale, nose.scale, nose.scale);
	RenderMesh(meshList[GEO_CONE], true);
	modelStack.PopMatrix();

	// Arm
	leftarm.scale = middle.scale;
	modelStack.PushMatrix();
	modelStack.Rotate(rotate, 0, 1, 0);
	//modelStack.Translate(body.translate.x, body.translate.y, body.translate.z);
	modelStack.Translate(middle.translate.x, middle.translate.y + (middle.scale*0.5f), middle.translate.z + middle.scale);
	modelStack.Rotate(leftarm.rotate, 1, 0, 0);
	modelStack.Scale(leftarm.scale, leftarm.scale, leftarm.scale);
	RenderMesh(meshList[GEO_CYL], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(rotate, 0, 1, 0);
	//modelStack.Translate(body.translate.x, body.translate.y, body.translate.z);
	modelStack.Translate(middle.translate.x, middle.translate.y + (middle.scale * 0.5f), middle.translate.z - middle.scale);
	modelStack.Rotate(-leftarm.rotate, 1, 0, 0);
	modelStack.Scale(leftarm.scale, leftarm.scale, leftarm.scale);
	RenderMesh(meshList[GEO_CYL], true);
	modelStack.PopMatrix();

	//RenderFacingText(meshList[GEO_TEXT], "Bow down to me", WHITE, 1, head.translate.x, head.translate.y + head.scale + (head.scale*0.2f), head.translate.z);
}

void AssignmentScene2::RenderCastle() {
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_CASTLEWALL], true);
	modelStack.PopMatrix();

}

void AssignmentScene2::RenderTree(float x, float y, float z, float size, float rotate) {
	modelStack.PushMatrix();
	modelStack.Translate(x, y+size*2, z);
	modelStack.Scale(size, size, size);
	RenderMesh(meshList[GEO_TREETOP], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(x, y, z);
	modelStack.Scale(size, size, size);
	RenderMesh(meshList[GEO_TREEBARK], true);
	modelStack.PopMatrix();
}

void AssignmentScene2::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z, 
		camera.target.x, camera.target.y, camera.target.z, 
		camera.up.x, camera.up.y, camera.up.z
	);
	modelStack.LoadIdentity();

	if (light[0].type == Light::LIGHT_DIRECTIONAL) {
		Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;

		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	} else if (light[0].type == Light::LIGHT_SPOT) {
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);

		Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	} else {
		Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}

	RenderSkybox();
	RenderCastle();

	/*modelStack.PushMatrix();
	objects[GEO_HOUSE1].scale = 0.1f;
	modelStack.Scale(objects[GEO_HOUSE1].scale, objects[GEO_HOUSE1].scale, objects[GEO_HOUSE1].scale);
	RenderMesh(meshList[GEO_HOUSE1], true);
	modelStack.PopMatrix();*/

	modelStack.PushMatrix();
	objects[GEO_HOUSE2].translate.x = 5;
	modelStack.Translate(objects[GEO_HOUSE2].translate.x, objects[GEO_HOUSE2].translate.y, objects[GEO_HOUSE2].translate.z);
	//modelStack.Scale(0.1, 0.1, 0.1);
	RenderMesh(meshList[GEO_HOUSE2], true);
	modelStack.PopMatrix();

	objects[GEO_TREE].translate.z = -30;
	for (int i = -30; i < 30; ++i) {
		objects[GEO_TREE].translate.x = i * 1.3f;
		objects[GEO_TREE].translate.z += 0.3f;
		objects[GEO_TREE].scale = 0.7f;
		RenderTree(objects[GEO_TREE].translate.x, objects[GEO_TREE].translate.y, objects[GEO_TREE].translate.z, objects[GEO_TREE].scale, 0);
	}

	for (unsigned i = 5; i < 15; i++) {
		RenderA01Character(i * 1.5f, 0.4f, 0, 0.6f, 90);
	}

	RenderGun();
}

void AssignmentScene2::Exit() {
	for (unsigned i = 0; i < NUM_GEOMETRY; i++) {
		if (meshList[i]) delete meshList[i];
	}
	//delete[] objects;
	glDeleteProgram(m_programID);
}

void AssignmentScene2::Reset() {
	camera.Init(Vector3(5, 0.4, 5), Vector3(1, 0.5, 1), Vector3(0, 1, 0), float(45.0f));
	light[0].position.Set(15, 35, 15);
	Mtx44 projection; projection.SetToPerspective(camera.fov, 40.0f / 30.0f, 0.1f, bounds);
	projectionStack.LoadMatrix(projection);

	head.translate.x = 0;
	head.translate.y = 6.9;
	head.translate.z = 0;
	head.rotate = 0;
	head.scale = 1.2;

	lefteye.scale = 0.2;

	body.translate.x = 0;
	body.translate.y = 0;
	body.translate.z = 0;
	body.scale = 3;

	middle.translate.x = 0;
	middle.translate.y = 4;
	middle.translate.z = 0;
	middle.scale = 2;

	nose.rotate = -90;
	nose.scale = 0.5;

	leftarm.rotate = 40;
	leftarm.scale = 0.3;

	hail.scale = 0.05;
	hail.translate.y = 10;

	object.translate.z = -10;
	object.translate.y = head.translate.y;
	object.scale = 0.7;
}