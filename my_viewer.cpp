
# include "my_viewer.h"

# include <sigogl/ui_button.h>
# include <sigogl/ui_radio_button.h>
# include <sig/sn_primitive.h>
# include <sig/sn_transform.h>
# include <sig/sn_manipulator.h>

# include <sigogl/ws_run.h>

SnGroup* g = new SnGroup;
SnGroup* frameGroup = new SnGroup;
SnGroup* frontwheelGroup = new SnGroup;
SnGroup* backwheelGroup = new SnGroup;
SnGroup* leftfootGroup = new SnGroup;
SnGroup* rightfootGroup = new SnGroup;
SnGroup* seatGroup = new SnGroup;
SnGroup* handlebarsGroup = new SnGroup;
SnModel* model[7];
SnTransform* t[7];
GsMat m[7];

bool _hand = false;
bool _uArm = false;
bool _lArm = false;

float x1, y, z1;
float x2, y2, z2;
float x3, y3, z3;
float x4, y4, z4;
float x5, y5, z5;
float x6, y6, z6;
float x7, y7, z7;


MyViewer::MyViewer(int x, int y, int w, int h, const char* l) : WsViewer(x, y, w, h, l)
{
	_nbut = 0;
	_animating = false;
	build_ui();
	build_scene();
}

void MyViewer::build_ui()
{
	UiPanel* p, * sp;
	UiManager* uim = WsWindow::uim();
	p = uim->add_panel("", UiPanel::HorizLeft);
	p->add(new UiButton("View", sp = new UiPanel()));
	{	UiPanel* p = sp;
	p->add(_nbut = new UiCheckButton("Normals", EvNormals));
	}
	p->add(new UiButton("Animate", EvAnimate));
	p->add(new UiButton("Exit", EvExit)); p->top()->separate();
}

void MyViewer::add_model(SnShape* s, GsVec p)
{
	// This method demonstrates how to add some elements to our scene graph: lines,
	// and a shape, and all in a group under a SnManipulator.
	// Therefore we are also demonstrating the use of a manipulator to allow the user to
	// change the position of the object with the mouse. If you do not need mouse interaction,
	// you can just use a SnTransform to apply a transformation instead of a SnManipulator.
	// You would then add the transform as 1st element of the group, and set g->separator(true).
	// Your scene graph should always be carefully designed according to your application needs.

	SnManipulator* manip = new SnManipulator;
	GsMat m;
	m.translation(p);
	manip->initial_mat(m);

	SnGroup* g = new SnGroup;
	SnLines* l = new SnLines;
	l->color(GsColor::orange);
	g->add(s);
	g->add(l);
	manip->child(g);
	// manip->visible(false); // call this to turn off mouse interaction

	rootg()->add(manip);
}

void MyViewer::build_scene()
{
	SnPrimitive* p;
	p = new SnPrimitive(GsPrimitive::Cylinder, 25, 25, 25.0f); // watch face
	p->prim().material.diffuse = GsColor::darkblue;
	p->prim().orientation = GsQuat(GsVec::i, (float)GS_PIDIV2);

	for (int i = 0; i < 7; i++) {
		model[i] = new SnModel;
		t[i] = new SnTransform;
	}

	// check to see if path is correct
	// ../../newhandlebars.obj
	if (!model[0]->model()->load("C:/Users/mnguyen287/Downloads/sigapp/obj files/newhandlebars.obj")) {
		gsout << "handlebars not loaded" << gsnl;
	}
	//model[0]->model()->centralize();
	//model[0]->model()->get_bounding_box(b0);
	handlebarsGroup->add(t[0]);
	handlebarsGroup->add(model[0]);
	x1 = 20.0f;
	y = 15.0f;
	z1 = 0.0f;
	m[0].translation(GsVec(x1, y, z1));
	t[0]->set(m[0]);
	handlebarsGroup->separator(true);

	if (!model[1]->model()->load("C:/Users/mnguyen287/Downloads/sigapp/obj files/frame.obj")) {
		gsout << "frame not loaded" << gsnl;
	}
	
	frameGroup->add(t[1]);
	frameGroup->add(model[1]);
	//model[1]->model()->centralize();
	//model[1]->model()->get_bounding_box(b1);
	x2 = 0.0f;
	y2 = 0.0f;
	z2 = 0.0f;
	m[1].translation(GsVec(x2, y2, z2));
	t[1]->set(m[1]);
	frameGroup->separator(true);

	if (!model[2]->model()->load("C:/Users/mnguyen287/Downloads/sigapp/obj files/seat.obj")) {
		gsout << "seat not loaded" << gsnl;
	}
	
	seatGroup->add(t[2]);
	seatGroup->add(model[2]);
	//model[2]->model()->centralize();
	//model[2]->model()->get_bounding_box(b2);
	x3 = -1.0f;
	y3 = 17.0f;
	z3 = 0.0f;
	m[2].translation(GsVec(x3, y3, z3));
	t[2]->set(m[2]);
	seatGroup->separator(true);

	if (!model[3]->model()->load("C:/Users/mnguyen287/Downloads/sigapp/obj files/backwheel.obj")) {
		gsout << "backwheel not loaded" << gsnl;
	}
	backwheelGroup->add(t[3]);
	backwheelGroup->add(model[3]);
	model[3]->model()->centralize();
	//model[3]->model()->get_bounding_box(b3);
	x4 = -11.0f;
	y4 = -5.0f;
	z4 = 0.0f;
	m[3].translation(GsVec(x4, y4, z4));
	t[3]->set(m[3]);
	backwheelGroup->separator(true);

	if (!model[4]->model()->load("C:/Users/mnguyen287/Downloads/sigapp/obj files/left foot.obj")) {
		gsout << "left foot not loaded" << gsnl;
	}
	leftfootGroup->add(t[4]);
	leftfootGroup->add(model[4]);
	//model[4]->model()->centralize();
	//model[4]->model()->get_bounding_box(b4);
	x5 = 2.0f;
	y5 = -4.0f;
	z5 = -4.0f;
	m[4].translation(GsVec(x5, y5, z5));
	t[4]->set(m[4]);
	leftfootGroup->separator(true);

	if (!model[5]->model()->load("C:/Users/mnguyen287/Downloads/sigapp/obj files/right foot.obj")) {
		gsout << "right foot not loaded" << gsnl;
	}
	rightfootGroup->add(t[5]);
	rightfootGroup->add(model[5]);
	//model[5]->model()->centralize();
	//model[5]->model()->get_bounding_box(b5);
	x6 = 6.0f;
	y6 = -6.0f;
	z6 = 1.0f;
	m[5].translation(GsVec(x6, y6, z6));
	t[5]->set(m[5]);
	rightfootGroup->separator(true);

	if (!model[6]->model()->load("C:/Users/mnguyen287/Downloads/sigapp/obj files/frontwheel.obj")) {
		gsout << "frontwheel not loaded" << gsnl;
	}
	frontwheelGroup->add(t[6]);
	frontwheelGroup->add(model[6]);
	model[6]->model()->centralize();
	//model[6]->model()->get_bounding_box(b6);
	x7 = 25.0f;
	y7 = -5.0f;
	z7 = 0.0f;
	m[6].translation(GsVec(x7, y7, z7));
	t[6]->set(m[6]);
	frontwheelGroup->separator(true);

	for (int i = 0; i < 7; i++) {
		g->add(t[i]);
		g->add(model[i]);
	}

	rootg()->add(frameGroup);
	rootg()->add(frontwheelGroup);
	rootg()->add(backwheelGroup);
	rootg()->add(leftfootGroup);
	rootg()->add(rightfootGroup);
	rootg()->add(seatGroup);
	rootg()->add(handlebarsGroup);
}

// Below is an example of how to control the main loop of an animation:
void MyViewer::run_animation()
{
	if (_animating) return; // avoid recursive calls
	_animating = true;

	//int ind = gs_random(0, rootg()->size() - 1); // pick one child
	//SnManipulator* manip = rootg()->get<SnManipulator>(0); // access one of the manipulators
	//GsMat m = manip->mat();

	//double frdt = 1.0 / 30.0; // delta time to reach given number of frames per second
	//double v = 4; // target velocity is 1 unit per second
	//double t = 0, lt = 0, t0 = gs_time();
	GsMat r, trans, trans2;

	while(_animating == true)
	{
		//while (t - lt < frdt) { ws_check(); t = gs_time() - t0; } // wait until it is time for next frame
		//lt = t;

		r.rotx((float)GS_2PI / 60.0f);

		if (_hand == true) {	
			t[2]->get() = t[2]->get() * r;
		}

		if (_uArm == true) {
			//trans.translation(GsVec(0, 0, 0));
			//t[1]->get() = t[1]->get() * trans;
			t[1]->get() = t[1]->get() * r;
		}

		if (_lArm == true) {
			t[0]->get() = t[0]->get() * r;
		}
		
		//manip->initial_mat(m);
		render(); // notify it needs redraw
		//ws_check(); // redraw now
	_animating = false;
	} 
}

void MyViewer::show_normals(bool view)
{
	// Note that primitives are only converted to meshes in GsModel
	// at the first draw call.
	GsArray<GsVec> fn;
	SnGroup* r = (SnGroup*)root();
	for (int k = 0; k < r->size(); k++)
	{
		SnManipulator* manip = r->get<SnManipulator>(k);
		SnShape* s = manip->child<SnGroup>()->get<SnShape>(0);
		SnLines* l = manip->child<SnGroup>()->get<SnLines>(1);
		if (!view) { l->visible(false); continue; }
		l->visible(true);
		if (!l->empty()) continue; // build only once
		l->init();
		if (s->instance_name() == SnPrimitive::class_name)
		{
			GsModel& m = *((SnModel*)s)->model();
			m.get_normals_per_face(fn);
			const GsVec* n = fn.pt();
			float f = 0.33f;
			for (int i = 0; i < m.F.size(); i++)
			{
				const GsVec& a = m.V[m.F[i].a]; l->push(a, a + (*n++) * f);
				const GsVec& b = m.V[m.F[i].b]; l->push(b, b + (*n++) * f);
				const GsVec& c = m.V[m.F[i].c]; l->push(c, c + (*n++) * f);
			}
		}
	}
}

int MyViewer::handle_keyboard(const GsEvent& e)
{
	int ret = WsViewer::handle_keyboard(e); // 1st let system check events
	if (ret) return ret;

	GsMat rotate;
	GsMat tranz;

	switch (e.key)
	{
	case GsEvent::KeyEsc: gs_exit(); return 1;
	case 'n': { bool b = !_nbut->value(); _nbut->value(b); show_normals(b); return 1; }
	case 'q':
		rotate.rotz((float)GS_2PI / 360.0f);
		tranz = t[3]->get();
		t[3]->get().mult(tranz, rotate);
		render();
		return 1;
	case 'a':
		rotate.rotz((float)GS_2PI / -360.0f);
		tranz = t[3]->get();
		t[3]->get().mult(tranz, rotate);
		render();
		return 1;
	case 'w':
		rotate.rotz((float)GS_2PI / 360.0f);
		tranz = t[6]->get();
		t[6]->get().mult(tranz, rotate);
		render();
		return 1;
	case 's':
		rotate.rotz((float)GS_2PI / -360.0f);
		tranz = t[6]->get();
		t[6]->get().mult(tranz, rotate);
		render();
		return 1;
	case 'e':
		rotate.roty((float)GS_2PI / 360.0f);
		tranz = t[2]->get();
		t[2]->get().mult(tranz, rotate);
		render();
		return 1;
	case 'd':
		rotate.roty((float)GS_2PI / -360.0f);
		tranz = t[2]->get();
		t[2]->get().mult(tranz, rotate);
		render();
		return 1;
	case 'r':
		rotate.rotz((float)GS_2PI / 360.0f);
		tranz = t[4]->get();
		t[4]->get().mult(tranz, rotate);
		render();
		return 1;
	case 'f':
		rotate.rotz((float)GS_2PI / -360.0f);
		tranz = t[4]->get();
		t[4]->get().mult(tranz, rotate);
		render();
		return 1;
	case GsEvent::KeySpace:
		camera().eye.x = 0;
		camera().eye.y = 100;
		camera().eye.z = 0;
		render();
		return 1;

	default: gsout << "Key pressed: " << e.key << gsnl;
	}

	return 0;
}

int MyViewer::uievent(int e)
{
	switch (e)
	{
	case EvNormals: show_normals(_nbut->value()); return 1;
	case EvAnimate: run_animation(); return 1;
	case EvExit: gs_exit();
	}
	return WsViewer::uievent(e);
}
