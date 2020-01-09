#include "pch.h"
#include "menu.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "variables.h"
#include "stb_image.h"

menu hack_menu;

GLFWwindow* window; //should be a private member but... to lazy
ImVec2 border_size = ImVec2(540, 500);

int my_image_width = 0;
int my_image_height = 0;
GLuint my_image_texture = 0;

void menu::init() {
	if (!glfwInit()) 
		MessageBoxA(NULL, "failed to init glfw, the program is probably going to crash...", "Error", MB_OK);

	window = glfwCreateWindow(680, 700, "Kyle menu >:)", NULL, NULL);

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); //vsync

	gl3wInit();

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();

	//would add back if could figure out how to load image from memory and not from static file path
	//IM_ASSERT(loadTextureFromFile("C:\\Users\\xaist\\source\\repos\\haloCE-internal\\haloCE-internal\\assets\\supersaist.png", &my_image_texture, &my_image_width, &my_image_height));
}

void menu::shutdown() {
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	glfwMakeContextCurrent(window);
	glfwSetWindowShouldClose(window, 1);
	glfwDestroyWindow(window);
	glfwTerminate();
}

void drawMainTab() {
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	ImGui::BeginChild("main", ImVec2(width, height), false);
	{
		ImGui::Text("Welcome to Kyle's halo combat evolved hacks. Enjoy your stay!");
		ImGui::Spacing();
		ImGui::Text("Close this window once ur done to clean up hack");

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();

		if (ImGui::Button("I don't care", ImVec2(100, 50))) {
			settings::aim_enabled = true;
			settings::esp_enabled = true;
			settings::tracers_enabled = true;
			settings::lock_health = true;
			settings::lock_shield = true;
			settings::lock_frag_grenades = true;
			settings::lock_plasma_grenades = true;
			settings::speed = true;
		}

		//pretty guud
		{
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$MIFFFFFFIIMMMNN$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$NIVVVVVVVVVVVVVVVIIMN$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$N$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$NIVVVVVVVVVVVVVVVVVVVVVVFIMN$$$$$$$$$$$$$$$$$$$$$$$NMMMMMFM$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$MVVVVVVVVVVVVVVVVVVVVVVVVVVVVIMN$$$$$$$$$$$$$$$$$MMFVMNMMMIM$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$MN$$$$$$$$$$$$$$$$$$$$$$$$$$$NIVVVVVVVVVVVVVFVVVVFVVVVVVVVVVVVVFIM$$$$$$$$$$$NMFVVFMNMMMMIM$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$V*N$$$$$$$$$$$$$$$$$$$$$$$$$MVVVFVVVVVVVVVVVI*:.:FFIFVVVVVVVVVVVIMV*M$VV$$NIVVVVVMNMMMMMMIM$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$V**M$$$$$$$$$$$$$$$$$$$$$$$IVVIMMMMIIFVVVVVVI******VVFVVVVVVVVFI*:.:V**IMIVVVVVFNNNNMMMMMIM$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$NMN$$$$$$$$$F***F$$$$$$$$$$$$$$$$$$$$NIVFMMMMMMMMMMIIFVVI:.:V**.:VIVVVVVVIV:..**:*MFVVVVVVINF*VNMMMMMIM$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$M*VIN$$$$$$I*****I$$$$$$$$$$$$$$$$NIVVMMMMMMMMMMMMMMMMMI....:V*::IIMMMMV:...:.:IIVVVVVVVMF:..VMMMMMMMN$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$I***FN$$$$M******VM$$$$$$$$$$$$NMFVFMMMMMMMMMMMMMMMMMMI.....:V**VIIMNV......*MFVVVVVVVIV:...VMMMNNNMM$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$NF****VM$$N********VM$$$$$$NMFFFVVFMMMMMMMMMMMMMMMMMMMF.......*V*:*NI*.:::.*IFVVVVVVFI*:....VNNMIIMIM$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$NV*****VMNV*********VM$$$NFVVVVVIMMMMMMMMMNMMMMMMMMMMF........*V:*MV****:*IVVVVVVVFF*:..:*VIIVFMNMIN$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$NMVV*****VIFINMIIFVV**INIVVVVVFMMMMI:V*....::*VMMMMMMF.........:V::V*VV*VFVVVVVVVMMMMVFM$MFIIMMMMMIN$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$MFFV*******VVMMVVFIIMMMFVVVVVFMMMMMI.**........:*IMMMF...:....:::VVFIVVMFVVVVVVVMM*I$$NMIMNNMMMMMMM$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$N*VVV*********FMFVVVVVVVVVVVFMMMMMNMFIV...........*MMI..**....*****IIFMFVVVVVVVMV*:M$MFVVVINMMMMMMM$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$I**VV**********IMFVVVVVVVVIMMMMMNNMV*V............*IF.***.......*V:VIVVVVVVVFM**:*MIMFVVVVVMNMMMMN$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$MV**VV**********VMMVVVVVVIMMMMMMNNMV*V:.....::....V:V:V**.......:VVFVVVVVVVFMV*:.*MVMMVVV****MMMMN$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$NV****************VMIFVVIMMMMMMMNNMN*V*.....****.:*.VVV*V.......*V:VVVVVVVFNIVVVVIMVVIV*:::::*IMN$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$FV*****************VMMMNMMMIMMIMMMMVVV:....****VFV.*MIV*......:IMFIVVVVVMNIVVVVMFIMFVMF**:::::V$$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$IVV******************VV**VVVVVIINNMN**V*:..:****VF:*VV*:::**VVIIFVVVVVVMNFVVV**ININMV*I**::::::V$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$MVVV**********************VVV*VIMNMMI**V:...::::*I**VMNMMMMIFVVVVVVVVFMMNIV*:::VNNMMV*FVV*::::::V$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$MVV***********************VVV*VINMMMVVV:.......*VMVVMIVVVVVVVVVVVVVINN*MMV*:***MFMMMV*IV*:::::::VN$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$NIVV**********************VVV**MINIVIVF*...:*VINNMFVVVVVVIIIIMMMMMV*I**MIV**V*FVVN$NFMIV*:::::*:*I$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$NMIV***********************VVV*FMMVVV*:FVVIMNNMMMIVVFIMMIFVV*MFV***VM***MV**MVVV:I$$$$MF*:::::VV**F$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$MFIFV**********************VVVVMVVVMFVMVFMMMMMMNMMMIFVMMIFVIMF*::**MV*:VIV*MNVF:VN$$$MF*:::::*$NIVFN$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$MMIIIIIIFFFV*****VNMMMMMIFVV*****VVFIMMMFIIVVMMMNMIVVIVV***MFM*:VIIMMNNNNFV*:VFVMIMM:V*:V$NI*:*:::*N$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$NMFVVVFVVVVV***FV:::****VFMMV***VVNMVVFIFIMNMV***:*V**...IIF:*I$$$$$$$$$$I*:VVMVVN:V*.*M$M*:V*::*M$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$NMFVVVVVVVVVMV::::::::::*VMI*VMFVVFMMMIMV::...:***:...IMFI$$NNMVVV*VFII:.*VMV:V*VFV:M$N*:VV*::M$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$MIVVVVVVVVVVVVMV:::::::::::::VNIVIMNV**VV:...:::M**:**INMM$$NNMM*...::::::..*M*:::VF*.M$$*:VV*::I$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$MVVVVVVVVVVVVVVMV:::::::*****VMFVM$I*..*MV*.:***MNVVVV*FNI$$NMMIF*:...:::....:V*...VF*.I$$*:IFV*:F$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$MVVVVVVVVVVVVVVVMV:::::::**VVIMVFMVV*...:V$N****INIIF*::*NM$NMIFIFVVVV.........::...*V*.F$$**NNIV*V$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$IVVVVVVVVVVVVVVVVMV:::::::::VMFFMN*..V*.:*VMIM*VII$VVV*::*IN$MFIIFI*:*M..............***.V$N*V$$$MVV$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$NMMMMIIIFVVVVVVVVVIV::::::::VMVFMMM*:::VV*VNNVFFFVIVM*VV*::V$$MF*VMI*:*M:.............:V*:VMI*M$$$$NM$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$NNMIFVVVVFI::::::*VIVIMMMMMMV.:VFIMNFVVVIV:M**V*::*MINI**V*::*N:................:FNVF$$$$$$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$MIVVVM*::::*FIVMMMMMMMM*:**VFNNFVVVM*:VV:**:::VV*MF****VIM:................:M$M$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$N$V::::VNIFIMMMMMMMFVVMNIV*VVVVINIVM*:::::*IF::****::.................:INVM$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$M****VVFMMMMMMMMNNFV**::*VVVVVIMN$M*:*:::*MV*:::...................:IMV*INMFI$$$NI$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$MV*V**:*FMMNNNNM*::::**VVVVVVIM$$$I***:::VMF*:.::::******VVV:....*MNFFMNMV**N$N**N$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*:::*VVVVVFMNV:::*VFVVVVVVFIM$$$$M*FF*::V*:::***::::***FM*..*VM$$NN$$NIIMIFM**:M$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*:*VVVVVVFMFM*:*VIIMVVVVVVIIN$$$$$MVMNV**VV::**::::::::**:*FN$$$$$$$M****IFFF*:V$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$V*VVVVVVMIVVI*VMFVVMVVVVVVFM$$V:**VFMNNMV*IMVV*:::::::**FMN$$NN$NN$$$F*:VINVMV**N$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$V*VVFM$NVVVVVIVVVMIVVVVVVFN$I::.....*V*INMN$$$$$NNNNN$$MVVVM*:V:.*F$$$V:*MNMIIVN$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$VVM$$$$MVVFMVVVVNIVVIFVVIM***VV.......:VI$MV*VFMN$M**F$NMMM:*V...*N$$M:*MFVV*VIM$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$MVFIVVVM$IVVMIVVIFMV:.F*.......:VMNV*:..::**:IV*VNMVFF::.*NMM$II$MI***VIN$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$NFVVVI$$MFVM$MMNMIMV.*N*.....:**FMIFV:....:MF:..VV**I*::VMFVVFIN$$NVV$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$NII$$$$NMVV*::.:VM:*IV*:...:*VMIIFVFMMMINI*:.VVVNMNNNMMNNMIVV*VVIN$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$I*VVMNMMIMNMIMF:......:*N**VI*:...:*VIFIFFVVVINNV**V*.VNNMMMFVM$$$NIV****VFM$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$I:..:::..:VVVVMV......:*MV**VV:.:****FFMVVFVVMMIVV*V:*MFVFIIFVN$$$$$$MV******VIN$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$V.....:..*IVVVM*.....:*II*VM*****VIMVIIIIVVVFNMVVV*VV**::::::M$$$$$$$$$NIV*****VVM$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$MV:.::**..*MVVVM*....:*I$M*VV***VIN$IVMVVVVFIFI$$NNVNNIV**::::M$$$$$$$$$$$$MV******VVM$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$V::.:::*M:.VNFIIMV::*VM$$$NVV**VFMNNMMFMFIIMMIIMN$INN$$$$$MIVVF$$$$$$$$$$$$$$$NIVVVVV**VI$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$M:**::::*FVVMMMN$N$$$$$$$$$$MIMFVVVMMMNMMMMMMNNNMV*FV$$$$$$$$$$$$$$$$$$$$$$$$$$$$$MMNF**VN$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$MV::::::**V$$$$$$$$$$$$$$$NVNF***VVIN$NMIFIVIMVVVVIV$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$IVI$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$V**VVVVVI$$$$$$$$$$$$$$NNM*VMV***VNNV*:..V:*F*:.:*VM$$$N$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$M***MFVV*****************MN$NV*....:FI**I*......:F:*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$M*::*V:.........:::::****VMMV:.....:FNIVFV**:....:V.*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$NVVV*F***:..........:**V**VV:.......VVMNNM****:...*IVM$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$IVVII*::.......::******V*V*.:......*VVNNMNV*:**.::VFFN$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$N:..V*....:::.....::**VVV.*V*:.....***V$$NNM*:...:VI*IMVFIMMN$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$***V::*****:.....:::*VVI*VMV.....:***I$NNMNF:...:FVINMMFVVVVIMN$$$$$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$M*:VVIVV*::::::::::::*INMI*VVIV.:::::NMNMMMNV..:VIVMMMMMMFVVVVVMN$$$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$F***VV*VF*VNNNNNIIIMMMMMIIV*VVVV:...VMVINMMNN*.:FVMMMMIMMMMIVVVVVIM$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$NIIV:**:VMMMNIVVFMMMMMIVVMIV:**IVVVMIVVIMMMNNVV:*MMMMMFIMMMMFVVVVVM$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$NVVVMMMNMFVVIMMMMMMVVVIMI**F*:*.:IVVVIMMMNNV:FMMMMMMFVIMMMIVVVVF$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$MNMMMMNMFVVFMMMMMMMVVVVMMMIFFIVMFFFVVVVIMMNMIIVFMMMMMMIVVIMMMFVVM****N$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$NV*:*NMMNMVVVIMMMMMMMIVVVFMMMFVVVVVVVVVVVVVIMMNMVVVFMMMMMMMVVFMMMIFF:..:N$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$N*:*VMMNIVVVIMMMMMMMMIVVVFMMIVVVVVVVVVVVVVVVMMMMFVVVFMMMMMMMVVVIMMMM*:.*$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$VV**MNFVVFMMMMMMMMMMVVVVIMMVVVVVVVVVVVVVVVVVMMMMVVVVFMMMMMMMFVVIMV*VV*M$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$MV**IIVVIMMMMMMMMMMIVVVVIMFVVVVVVVVVVVVVVVVVVMMMFVVVVVMMMMMMMFVVM*:..*M$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$NFVVMIIMMMMMMMMMIMFVVVVMIVVVVVVVVVVVVVVVVVVVFMMMVVVVVVMMMMMMMVMV***:V$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$M*.*MMMMMMMMMMFIMVVVVVMVVVVVVVVVVVVVVVVVVVVVFMNFVVVVVVMMMMNMMMV*:IN$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$M*.**IMMMMMMMIVMMVVVVVFVVVVVVVVVVVVVVVVVVVVVVINMVVVVVFIVVF*VV*VFN$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$N**VV*MMMMMIVFMIVVVVVVVVVVVVVVVVVVVVVVVVVVVVVM$IVVVIM*..*V:..:I$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$NV*::*FMNMFVIMIVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVNMFIIIV**..:*.*VN$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$V.....*IVVIMMIVVVVVVVVVVVVVVVVVVVVVVVVVVVVFIN$V*.:V**:.*V**:VN$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$MV:..:V*::VVFVMMIIFVVVVVVVVVVVVVFFFIIMMMMVIIVF*:..*V*V**::****N$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$MV*VV*.*****V*VMMFMMIFMFVFMIVVIMFVVM*VV:***V***VMMMV***VV*:.*$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$M:::*F*:.*:V*.VV.**:VIVVI**F*:*M:.:V::F::***M$$$$$$NVVV****:.V$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$N**:.:*VVVV*I**V:.::.V****.*I***I:.:*VVM*.:*VN$$$$$$$I*******.:M$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$V.:**:.:::*N$$NNMV:..VIM*..*$$$$M*::I$$$MMN$$$$$$$$$$$F******:.*$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$M:...:***::I$$$$$$$MIIN$$MIIN$$$$$$NN$$$$$$$$$$$$$$$$$$$V**VVFV**$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*.........*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$NVMMMMMMIM$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$M:.........F$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$NMMVVFMFI$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$M:...::...*N$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$NMIMMMFI$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$MVVFIFFFV*V$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$NNNNNN$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$IFVIVVVFFI$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$MVVFFVVIMM$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$MVVVFMMN$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$NMMMN$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$", 2);
			ImGui::Text("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$", 2);
		}
		//ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2(my_image_width, my_image_height));
	}
	ImGui::EndChild();
}

const char* aimTargetSelection[] = { "Crosshair", "Distance" };

void drawFunTab() {
	ImGui::BeginChild("aimbot", ImVec2(330, 400), true);
	{
		ImGui::Text("Aimbot");  
		ImGui::Spacing();
		ImGui::Checkbox("enabled", &settings::aim_enabled);
		//if (ImGui::IsItemHovered()) ImGui::SetTooltip("Auto aim so you don't have to move your mouse");
		ImGui::Spacing();
		ImGui::RadioButton("Hold (rmb)", &settings::aim_style, 0); ImGui::SameLine();
		ImGui::RadioButton("Tap (lalt)", &settings::aim_style, 1); ImGui::SameLine();
		ImGui::RadioButton("Fov (lalt", &settings::aim_style, 2);
		ImGui::Spacing();
		ImGui::Combo("##AimTargetSelection", &settings::aim_selection_style, aimTargetSelection, IM_ARRAYSIZE(aimTargetSelection));
		ImGui::Checkbox("FOV", &settings::aim_fov_enabled); ImGui::SameLine();
		ImGui::InputFloat("##Size", &settings::aim_fov_size);
		//if (ImGui::IsItemHovered()) ImGui::SetTooltip("The priority of enemy selection");

		ImGui::Spacing(); ImGui::Spacing();

		ImGui::Checkbox("ESP", &settings::esp_enabled);
		//if (ImGui::IsItemHovered()) ImGui::SetTooltip("Draws enemy type, health, and distance at their position");
		ImGui::Checkbox("Tracers", &settings::tracers_enabled);
		//if (ImGui::IsItemHovered()) ImGui::SetTooltip("Draws a line from your crosshair to enemy position");
		ImGui::Text("ESP Color:");
		ImGui::ColorEdit4("##EspColor", (float*)&settings::esp_color, ImGuiColorEditFlags_NoLabel);
	}
	ImGui::EndChild();

	ImGui::SameLine();

	ImGui::BeginChild("playerstats", ImVec2(330, 270), true);
	{
		ImGui::Text("Player stuff");
		ImGui::Spacing();
		ImGui::Checkbox("Lock Health", &settings::lock_health);
		ImGui::Checkbox("Lock Shield", &settings::lock_shield);
		ImGui::Checkbox("Lock Frag Grenades", &settings::lock_frag_grenades);
		ImGui::Checkbox("Lock Plasma Grenades", &settings::lock_plasma_grenades);
	}
	ImGui::EndChild();
}

void drawMiscTab() {
	ImGui::BeginChild("misc", border_size, true);
	{
		ImGui::Text("This is pretty cool!!!!");

		ImGui::Spacing(); ImGui::Spacing();

		ImGui::Checkbox("Speed (F2)", &settings::speed); ImGui::SameLine();
		ImGui::InputFloat("##how fast", &settings::how_fast, 0.01);
		ImGui::Spacing();
		ImGui::Text("Game Speed"); ImGui::SameLine();
		ImGui::InputFloat("##Game Speed", &*reinterpret_cast<float*>(addr::GAME_SPEED), 1);
	}
	ImGui::EndChild();
}

void menu::tick() {
	glfwPollEvents();

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	int width, height;
	glfwGetWindowSize(window, &width, &height);

	ImGui::SetNextWindowSize(ImVec2(static_cast<float>(width), static_cast<float>(height)));
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::Begin("Halo Internal by Kyle", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	{
		static char buttons[][16] = { "main", "fun", "misc" };

		static int iTab = 0;
		for (int i = 0; i < 3; i++)
		{
			if (i > 0) ImGui::SameLine(0.0f, -0.3f);

			if (ImGui::Button(buttons[i], ImVec2(160, 30)))
				iTab = i;
		}
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();

		switch (iTab) {
		case 0: drawMainTab(); break;
		case 1: drawFunTab(); break;
		case 2: drawMiscTab(); break;
		}

		ImGui::End();
	}
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
}

GLFWwindow* menu::get_window() {
	return window;
}