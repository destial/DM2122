#include "AssignmentScene.h"
#include "Application.h"
#include "Utility.h"
#include <iostream>

AssignmentScene::AssignmentScene() {}

AssignmentScene::~AssignmentScene() {}

void AssignmentScene::Init() {
	glClearColor(0.4f, 0.4f, 0.4f, 0.0f);
	m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//LightSource.fragmentshader");
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
	glUseProgram(m_programID);

	light[0].type = Light::LIGHT_SPOT;
	light[0].position.Set(0, 10, 0);
	light[0].color = YELLOW;
	light[0].power = 5;
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

	glUniform1i(m_parameters[U_NUMLIGHTS], (sizeof(light)/sizeof(light[0])));
	
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	meshList[GEO_LIGHT] = MeshBuilder::GenerateSphere("light", YELLOW, 30, 30, 1);
	meshList[GEO_CYL] = MeshBuilder::GenerateCylinder("cyl", BROWN, 30, 0.6f, 10);

	meshList[GEO_CIRCLE] = MeshBuilder::GenerateCircle("floor", WHITE, 30, 1);

	meshList[GEO_CONE] = MeshBuilder::GenerateCone("cone", PURPLE, 30, 1, 5);

	meshList[GEO_SPHERE2] = MeshBuilder::GenerateSphere("dot", BLACK, 30, 30, 1);

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("body", WHITE, 30, 30, 1);

	Mtx44 projection; 
	projection.SetToPerspective(45.0f, 40.0f / 30.0f, 0.1f, 100.0f);
	projectionStack.LoadMatrix(projection);
	camera.Init(Vector3(25, 0, 3), Vector3(0, 0, 0), Vector3(0, 1, 0));

	Reset();

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void AssignmentScene::Update(double dt) {
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
	if (Application::IsKeyPressed('C')) {
		dt *= 5.0f;
	}

	unsigned LSPEED = 10.f;
	if (Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('K'))
		light[0].position.z += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('L'))
		light[0].position.x += (float)(LSPEED * dt);
	if (Application::IsKeyPressed('O'))
		light[0].position.y -= (float)(LSPEED * dt);
	if (Application::IsKeyPressed('P'))
		light[0].position.y += (float)(LSPEED * dt);

	camera.Update(dt);
	if (!complete) {
		if (hit) {
			if (head.translate.y >= body.translate.y - (0.6 * body.scale)) {
				head.translate.y -= 3 * dt;
				head.translate.z += 3 * dt;
				head.rotate -= 5 * dt;
			}
			else {
				if (!(middle.translate.y <= body.translate.y - (0.38 * body.scale))) {
					middle.translate.z += 3 * dt;
					middle.translate.z -= 3 * dt;
				}
				else {
					complete = true;
				}
			}
		}
		if (!hit) {
			unsigned RSPEED = LSPEED * 5.0f;
			if (reverse)
				leftarm.rotate += RSPEED * dt;
			else
				leftarm.rotate -= RSPEED * dt;
			if (leftarm.rotate >= 60) reverse = false;
			else if (leftarm.rotate <= 30) reverse = true;
		}

		if (object.translate.z >= head.translate.z - 1 || hit) {
			hit = true;
			object.translate.z = head.translate.z;
			object.translate.y = head.translate.y;
			object.translate.x = head.translate.x;
		}
		else {
			object.translate.z += 3 * dt;
		}
	}
	else {
		body.scale += 0.1 * dt;
		body.translate.y += 0.1 * dt;

		middle.scale += 0.1 * dt;
		middle.translate.y += 0.1 * dt;

		head.scale += 0.1 * dt;
		head.translate.y += 0.1 * dt;
	}
	hail.translate.y -= 5.0f * dt;
}

void AssignmentScene::RenderMesh(Mesh* mesh, bool enableLight) {
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
	mesh->Render();
}

void AssignmentScene::Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y,
		camera.position.z, camera.target.x, camera.target.y,
		camera.target.z, camera.up.x, camera.up.y, camera.up.z
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

	// Ground
	modelStack.PushMatrix();
	modelStack.Translate(0, -3, 0);
	modelStack.Scale(30, 30, 30);
	RenderMesh(meshList[GEO_CIRCLE], true);
	modelStack.PopMatrix();

	// Light ball
	modelStack.PushMatrix();
	modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
	modelStack.Scale(0.5, 0.5, 0.5);
	RenderMesh(meshList[GEO_LIGHT], false);
	modelStack.PopMatrix();

	// Bottom body
	modelStack.PushMatrix();
	modelStack.Translate(body.translate.x, body.translate.y, body.translate.z);
	modelStack.Scale(body.scale, body.scale, body.scale);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();

	// Middle body
	modelStack.PushMatrix();
	modelStack.Translate(middle.translate.x, middle.translate.y, middle.translate.z);
	modelStack.Scale(middle.scale, middle.scale, middle.scale);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();

	// Head
	modelStack.PushMatrix();
	modelStack.Translate(head.translate.x, head.translate.y, head.translate.z);
	modelStack.Rotate(head.rotate, 1, 0, 0);
	modelStack.Scale(head.scale, head.scale, head.scale);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();

	// Eyes
	modelStack.PushMatrix();
	modelStack.Translate(head.translate.x + 1, head.translate.y + 0.3, head.translate.z - 0.6);
	modelStack.Rotate(head.rotate, 1, 0, 0);
	modelStack.Scale(lefteye.scale, lefteye.scale, lefteye.scale);
	RenderMesh(meshList[GEO_SPHERE2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(head.translate.x + 1, head.translate.y+0.3, head.translate.z + 0.6);
	modelStack.Rotate(head.rotate, 1, 0, 0);
	modelStack.Scale(lefteye.scale, lefteye.scale, lefteye.scale);
	RenderMesh(meshList[GEO_SPHERE2], true);
	modelStack.PopMatrix();

	// Middle dots
	modelStack.PushMatrix();
	modelStack.Translate(middle.translate.x + middle.scale - 0.2, middle.translate.y + 1, middle.translate.z);
	modelStack.Scale(lefteye.scale, lefteye.scale, lefteye.scale);
	RenderMesh(meshList[GEO_SPHERE2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(middle.translate.x + middle.scale, middle.translate.y, middle.translate.z);
	modelStack.Scale(lefteye.scale, lefteye.scale, lefteye.scale);
	RenderMesh(meshList[GEO_SPHERE2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(middle.translate.x + middle.scale - 0.2, middle.translate.y - 1, middle.translate.z);
	modelStack.Scale(lefteye.scale, lefteye.scale, lefteye.scale);
	RenderMesh(meshList[GEO_SPHERE2], true);
	modelStack.PopMatrix();

	// Bottom body dots
	modelStack.PushMatrix();
	modelStack.Translate(body.translate.x + body.scale - 0.7, body.translate.y + 2, body.translate.z);
	modelStack.Scale(lefteye.scale, lefteye.scale, lefteye.scale);
	RenderMesh(meshList[GEO_SPHERE2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(body.translate.x + body.scale - 0.2, body.translate.y + 1, body.translate.z);
	modelStack.Scale(lefteye.scale, lefteye.scale, lefteye.scale);
	RenderMesh(meshList[GEO_SPHERE2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(body.translate.x + body.scale, body.translate.y, body.translate.z);
	modelStack.Scale(lefteye.scale, lefteye.scale, lefteye.scale);
	RenderMesh(meshList[GEO_SPHERE2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(body.translate.x + body.scale - 0.2, body.translate.y - 1, body.translate.z);
	modelStack.Scale(lefteye.scale, lefteye.scale, lefteye.scale);
	RenderMesh(meshList[GEO_SPHERE2], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(body.translate.x + body.scale - 0.7, body.translate.y - 2, body.translate.z);
	modelStack.Scale(lefteye.scale, lefteye.scale, lefteye.scale);
	RenderMesh(meshList[GEO_SPHERE2], true);
	modelStack.PopMatrix();

	// Nose
	modelStack.PushMatrix();
	modelStack.Translate(head.translate.x+1, head.translate.y, head.translate.z);
	modelStack.Rotate(nose.rotate, 0, 0, 1);
	modelStack.Scale(nose.scale, nose.scale, nose.scale);
	RenderMesh(meshList[GEO_CONE], true);
	modelStack.PopMatrix();

	// Arm
	modelStack.PushMatrix();
	modelStack.Translate(middle.translate.x, middle.translate.y+0.5, middle.translate.z + 2.1);
	modelStack.Rotate(leftarm.rotate, 1, 0, 0);
	modelStack.Scale(leftarm.scale, leftarm.scale, leftarm.scale);
	RenderMesh(meshList[GEO_CYL], true);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(middle.translate.x, middle.translate.y+0.5, middle.translate.z - 2.1);
	modelStack.Rotate(-leftarm.rotate, 1, 0, 0);
	modelStack.Scale(leftarm.scale, leftarm.scale, leftarm.scale);
	RenderMesh(meshList[GEO_CYL], true);
	modelStack.PopMatrix();

	// Snow falling
	srand(time(NULL));
	for (unsigned i = 0; i < 100; i++) {
		float x = rand() % 40 - 20;
		float y = (rand() % 2 + 3) * hail.translate.y;
		if (y <= -5) {
			hail.translate.y = 5;
		}
		float z = rand() % 40 - 20;
		modelStack.PushMatrix();
		modelStack.Translate(x, y ,z);
		unsigned ran = rand() % 2 + 1;
		if (ran == 1)
			modelStack.Scale(hail.scale * 1.5, hail.scale * 1.5, hail.scale * 1.5);
		else if (ran == 2)
			modelStack.Scale(hail.scale * 0.5, hail.scale * 0.5, hail.scale * 0.5);
		else
			modelStack.Scale(hail.scale, hail.scale, hail.scale);
		RenderMesh(meshList[GEO_SPHERE], true);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Translate(object.translate.x, object.translate.y, object.translate.z);
	modelStack.Scale(object.scale, object.scale, object.scale);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();
}

void AssignmentScene::Exit() {
	for (unsigned i = 0; i < NUM_GEOMETRY; i++) {
		if (meshList[i]) delete meshList[i];
	}
	glDeleteProgram(m_programID);
}

void AssignmentScene::Reset() {
	light[0].position.Set(0, 10, 0);
	hit = false;
	complete = false;

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

	hail.scale = 0.2;
	hail.translate.y = 10;

	object.translate.z = -10;
	object.translate.y = head.translate.y;
	object.scale = 0.7;
}