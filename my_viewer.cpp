
# include "my_viewer.h"

# include <sigogl/ui_button.h>
# include <sigogl/ui_radio_button.h>
# include <sig/sn_primitive.h>
# include <sig/sn_transform.h>
# include <sig/sn_manipulator.h>

# include <sigogl/ws_run.h>

SnGroup* g = new SnGroup;
SnGroup* frameGroup = new SnGroup;
SnGroup* backwheelGroup = new SnGroup;
SnGroup* leftfootGroup = new SnGroup;
SnGroup* rightfootGroup = new SnGroup;
SnGroup* seatGroup = new SnGroup;
SnGroup* handlebarsGroup = new SnGroup;
SnModel* model[6];
SnTransform* t[6];
GsMat m[6];
GsBox b0, b1, b2, b3, b4, b5;

bool _hand = false;
bool _uArm = false;
bool _lArm = false;

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
	for (int i = 0; i < 6; i++) {
		model[i] = new SnModel;
		t[i] = new SnTransform;
	}

	// check to see if path is correct
	if (!model[0]->model()->load("C:/Users/mnguyen287/Desktop/handlebars.obj")) {
		gsout << "handlebars not loaded" << gsnl;
	}
	handlebarsGroup->separator(true);
	//model[0]->model()->centralize();
	model[0]->model()->get_bounding_box(b0);
	m[0].translation(GsVec(0.0f, 0.0f, b0.dz()) / 2.0f);
	t[0]->set(m[0]);

	if (!model[1]->model()->load("C:/Users/mnguyen287/Desktop/frame.obj")) {
		gsout << "frame not loaded" << gsnl;
	}
	frameGroup->separator(true);
	//model[1]->model()->centralize();
	model[1]->model()->get_bounding_box(b1);
	m[1].translation(GsVec(0.0f, 0.0f, b1.dz()));
	t[1]->set(m[1]);

	if (!model[2]->model()->load("C:/Users/mnguyen287/Desktop/seat.obj")) {
		gsout << "seat not loaded" << gsnl;
	}
	seatGroup->separator(true);
	//model[2]->model()->centralize();
	model[2]->model()->get_bounding_box(b2);
	m[2].translation(GsVec(0.0f, 0.0f, b2.dz()));
	t[2]->set(m[2]);

	if (!model[3]->model()->load("C:/Users/mnguyen287/Desktop/backwheel.obj")) {
		gsout << "backwheel not loaded" << gsnl;
	}
	backwheelGroup->separator(true);
	//model[3]->model()->centralize();
	model[3]->model()->get_bounding_box(b3);
	m[3].translation(GsVec(0.0f, 0.0f, b3.dz()) / 2.0f);
	t[3]->set(m[3]);

	if (!model[4]->model()->load("C:/Users/mnguyen287/Desktop/left foot.obj")) {
		gsout << "left foot not loaded" << gsnl;
	}
	leftfootGroup->separator(true);
	//model[4]->model()->centralize();
	model[4]->model()->get_bounding_box(b4);
	m[4].translation(GsVec(0.0f, 0.0f, b4.dz()));
	t[4]->set(m[4]);

	if (!model[5]->model()->load("C:/Users/mnguyen287/Desktop/right foot.obj")) {
		gsout << "right foot not loaded" << gsnl;
	}
	rightfootGroup->separator(true);
	//model[5]->model()->centralize();
	model[5]->model()->get_bounding_box(b5);
	m[5].translation(GsVec(0.0f, 0.0f, b5.dz()));
	t[5]->set(m[5]);

	for (int i = 0; i < 6; i++) {
		g->add(t[i]);
		g->add(model[i]);
	}

	rootg()->add(g);
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

void MyViewer::run_other_animation()
{
	if (_animating) return; // avoid recursive calls
	_animating = true;

	GsMat r;

	while (_animating == true)
	{
		r.rotx((float)-GS_2PI / 60.0f);
		//trans.translation(GsVec(0, 0, 0));

		if (_hand == true) {
			//t[2]->get() = t[2]->get() * trans;
			t[2]->get() = t[2]->get() * r;
		}

		if (_uArm == true) {
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

	switch (e.key)
	{
	case GsEvent::KeyEsc: gs_exit(); return 1;
	case 'n': { bool b = !_nbut->value(); _nbut->value(b); show_normals(b); return 1; }
	case 'q':
		_lArm = true;
		run_animation();
		return 1;
	case 'a':
		_lArm = true;
		run_other_animation();
		return 1;
	case 'w':
		_uArm = true;
		run_animation();
		return 1;
	case 's':
		_uArm = true;
		run_other_animation();
		return 1;
	case 'e':
		_hand = true;
		run_animation();
		return 1;
	case 'd':
		_hand = true;
		run_other_animation();
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
