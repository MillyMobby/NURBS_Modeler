#include "ImguiController.h"

void ImguiController::setIMGUI(GLFWwindow* _window) {
	
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	ImGui_ImplGlfw_InitForOpenGL(_window, true);
	ImGui_ImplOpenGL3_Init("#version 130");
}

void ImguiController::displayInputGuide() {
	static bool no_background = true;
	
	ImGui::SetNextWindowBgAlpha(0.2f); // Transparent background
	ImGui::Begin("Curve Settings");
	
	ImGui::Text("Keyboard input guide:");
	ImGui::BulletText("[F] = remove first control point");
	ImGui::BulletText("[L] = remove last control point");
	
	ImGui::Text("Mouse input guide:");
	ImGui::BulletText("[right] = add control point");
	ImGui::BulletText("[left] = move selected control point");
	ImGui::BulletText("[mouse wheel up] = zoom in");
	ImGui::BulletText("[mouse wheel down] = zoom out");
	ImGui::BulletText("[middle] = drag and drop to move the view \n\n");
}

void ImguiController::DegreeRangeWidget() {
	
	static int max;
	if (maxDegree > 0) minDegree = 1; max = maxDegree;
	ImGui::DragIntRange2("Degree Range", &minDegree, &maxDegree, 5, 0, 1000, "Min: %d", "Max: %d");
	if (maxDegree > max) maxDegree = max;
}

void ImguiController::degreeSlider() {
	if (grado < 0) grado = 2;
	if (maxDegree >= 1 && grado <= maxDegree) {

		if (ImGui::SliderInt("Degree Choice", &grado, 1, 10)) { showLerps = false; }
	}
}

void ImguiController::NurbsWeightEditor() {
	if (makeNURBS == true) {
		if (maxDegree >= grado) {
			//if (isChanged) { setPredefinedCurve(); isChanged = false; }
			ImGui::BulletText("NURBS weight slider:\n");
			int col = 0;
			float r, g, b;
			ImVec4 color=(ImVec4)::ImColor(0.7f, 0.3f, 0.4f);;
			for (int i = 0; i < maxDegree + minDegree; i++)
			{

				if (i > 0) ImGui::SameLine();
				ImGui::PushID(i);
				if (col > 5) col = 0;
				if (i % 2 == 0) { r = col / 7.0f; g = col / 5.0f;b= 0.4f; }
				else { r = 0.7f; g = 0.3f;b= col / 6.0f; }
				ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)::ImColor(r,g,b));
				ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, (ImVec4)ImColor(r,g,b));
				ImGui::PushStyleColor(ImGuiCol_FrameBgActive, (ImVec4)ImColor(r - 0.1f, g - 0.1f, b - 0.1f));
				ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor(r+0.1f,g+0.1f,b+0.1f));
				ImGui::VSliderFloat("##v", ImVec2(20, 160), &weights[i], 0.001f, 1.0f, "w");
				if (ImGui::IsItemActive() || ImGui::IsItemHovered())
					ImGui::SetTooltip("%.3f", weights[i]);
				
				ImGui::PopStyleColor(4);
				ImGui::PopID();
				col++;
			}
			for (int i = 0; i < maxDegree + minDegree; i++) { 
				if (i<9 ) {ImGui::TextColored((ImVec4)ImColor(0.9f,0.9f,0.9f), "w%d ", i); ImGui::SameLine();  }
				else { ImGui::TextColored((ImVec4)ImColor(0.9f, 0.9f, 0.9f), "w%d", i); ImGui::SameLine(); }
				
			}
			ImGui::NewLine();
			ImGui::Combo("mode", &item, "free curve\0circle\0\0");
			if (item != itemCurrent) { itemCurrent = item; setPredefinedCurve(); isChanged = true; }
			else isChanged = false;
		}
	}
	else if (makeNURBS == false) {
		if (maxDegree >= grado) { for (int i = 0; i < maxDegree + minDegree; i++) { weights[i] = 0.5f; } }
	}
}

void ImguiController::windowIMGUI(GLFWwindow* _window) {
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	
	//if (show_window)
		//ImGui::ShowDemoWindow(&show_demo_window);	
		//ImGuiIO& io = ImGui::GetIO();
	ImGui::GetIO().ConfigWindowsMoveFromTitleBarOnly = true;
	{
		displayInputGuide();
		const char* H[] = { curvesHierarchy[0], curvesHierarchy[1],curvesHierarchy[2],curvesHierarchy[3],curvesHierarchy[4],curvesHierarchy[5],curvesHierarchy[6],curvesHierarchy[7],curvesHierarchy[8],curvesHierarchy[9],curvesHierarchy[10],curvesHierarchy[11],curvesHierarchy[12],curvesHierarchy[13],curvesHierarchy[14],curvesHierarchy[15] };
		static int item_current = 0;
		if (ImGui::Button("Add New Curve")) { addCurve = 1; showLerps = false; }
		else addCurve = 0;
		ImGui::ListBox("Curve\nHierarchy", &selectedCurve, H, IM_ARRAYSIZE(H), 4);
		
		
		DegreeRangeWidget();
		degreeSlider();
		
		
		ImGui::SliderFloat("Curve Position", &t, 0.000f, 1.000f, "t = %.7f");
		if (t != tCurrent) { tCurrent = t; isChanged = true; }
		else isChanged = false;

		if (ImGui::Button("Split Curve  (Bezier)")) { splitCurve = 1; showLerps = false; }
		else splitCurve = 0;

		if (ImGui::Button("Degree Raise (Bezier)") && makeBezier) { degreeRaiseBezier = 1; showLerps = false; }
		else degreeRaiseBezier = 0;



		ImGui::Text("Control Points = % d\n", (maxDegree + minDegree));

		ImGui::Checkbox("Make Bezier", &makeBezier);
		ImGui::SameLine();
		ImGui::Text("(Degree %d)", maxDegree); ImGui::SameLine(); ImGui::Checkbox("Show De Casteljau/De Boor", &showLerps);
		ImGui::Checkbox("Make NURBS (Add Weights)", &makeNURBS);
		NurbsWeightEditor();
		ImVec2 window_pos = ImGui::GetWindowPos();
		 
		ImVec2 window_size = ImGui::GetWindowSize();		

		if ((maxDegree + minDegree)>grado && itemCurrent==0) ImGui::GetBackgroundDrawList()->AddCircle(tPoint, 1.9f, IM_COL32(255, 0, 0, 200), 0,  10);
		
		
		static ImVec2 scrolling(0.0f, 0.0f);
		ImVec2 canvas_p0 = ImVec2(0, 0);      // screen coordinates!
		ImVec2 canvas_sz = ImVec2((float)w,(float)h);   // Resize canvas to what's available
		if (canvas_sz.x < 50.0f) canvas_sz.x = 50.0f;
		if (canvas_sz.y < 50.0f) canvas_sz.y = 50.0f;
		ImVec2 canvas_p1 = ImVec2(canvas_p0.x + canvas_sz.x, canvas_p0.y + canvas_sz.y);
		ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
		draw_list->PushClipRect(canvas_p0, canvas_p1, true);
		
			const float GRID_STEP = 40.0f;
			for (float x = fmodf(scrolling.x, GRID_STEP); x < canvas_sz.x; x += GRID_STEP)
				draw_list->AddLine(ImVec2(canvas_p0.x + x, canvas_p0.y), ImVec2(canvas_p0.x + x, canvas_p1.y), IM_COL32(200, 200, 200, 40));
			for (float y = fmodf(scrolling.y, GRID_STEP); y < canvas_sz.y; y += GRID_STEP)
				draw_list->AddLine(ImVec2(canvas_p0.x, canvas_p0.y + y), ImVec2(canvas_p1.x, canvas_p0.y + y), IM_COL32(200, 200, 200, 40));
		

		ImGui::End();
	}
}

void ImguiController::renderIMGUI() {
	ImGui::Render();
	int display_w, display_h;
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImguiController::cleanupIMGUI() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void ImguiController::setPredefinedCurve() {
	std::vector<float> w;
	switch (itemCurrent) {
	case 0:
		break;
	case 1:		
		w = PredefinedCurves::getCircleWeights();
		makeBezier = false;
		maxDegree = w.size() - 1;
		for (int i = 0; i < maxDegree + minDegree; i++)
		{
			weights[i] = w[i];
		}
		break;
	default:
		break;
	}
}

void ImguiController::updateWeightsSliders(std::vector<float> w) {
	for (int i = 0; i < maxDegree + minDegree; i++)
	{
		weights[i] = w[i];
	}
}

void ImguiController::updateHierarchy(int activatedCurves) {
	if (activatedCurves <= 15) {
		for (int i = 0; i <= activatedCurves; i++) {
				std::string name = "Curve" + std::to_string(i+1);
				std::cout << name << std::endl;
				strcpy_s(curvesHierarchy[i], name.c_str());		
		}
	}	
}

void ImguiController::drawDecas(std::vector<Vec3d> pts) {
	for (int i = 0; i < pts.size(); i++) {
		
		ImGui::GetBackgroundDrawList()->AddCircle(ImVec2((pts[i].x + 1.0000f) * 0.5000 * double(1580), (1.0000f - pts[i].y) * 0.5000 * double(1000)), 1.9f, IM_COL32( 0, 255, 0,200), 0, 10);
	}
}







