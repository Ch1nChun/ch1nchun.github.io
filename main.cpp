 ImGui::BeginChild( "main", { window->Size.x - 81, window->Size.y - window->DC.CursorPos.y + window->Pos.y }, 0, ImGuiWindowFlags_NoBackground );
            {
                switch ( tab ) {
                case 0: {
                    ImGui::BeginChild( "subtabs", { ImGui::GetWindowWidth( ) - 30, 40 }, 1 );
                    {
                        ImGui::SetCursorPos( { 16, 0 } );

                        if ( custom::subtab( "General##subtab", subtab == 0 ) ) subtab = 0; ImGui::SameLine( 0, 20 );                  
                        if ( custom::subtab( "Exploits##subtab", subtab == 1 ) ) subtab = 1;
                    }
                    ImGui::EndChild( );
                    ImGui::BeginChild( "main_child", { ImGui::GetWindowWidth( ), ImGui::GetWindowHeight( ) - 55 }, 0, ImGuiWindowFlags_NoBackground );
                    {                   

                        ImGui::BeginGroup( );
                        {
                            custom::begin_child( "Weapon Settings", { ( ImGui::GetWindowWidth( ) - 30 ) / 2 - ImGui::GetStyle( ).ItemSpacing.x / 2, 0 } );
                            {
                                static bool enabled = false;
                                static int slider = 0;
                                static char text[64];
                                static float col[4];
                                static int combo = 0;

                                ImGui::Checkbox("Override weapon group##2", &enabled);
                                ImGui::Combo("Weapon Configuration", &combo, "General\0\rPistols\0\rHeavy pistols\0\rScout\0\rAuto snipers\0\rAWP");
                               
                            }
                            custom::end_child( );

                            custom::begin_child( "General Settings", { ( ImGui::GetWindowWidth( ) - 30 ) / 2 - ImGui::GetStyle( ).ItemSpacing.x / 2, 0 } );
                            {
                                static bool enabled = false;
                                static int fov_slider = 0;
                                static char text[64];
                                static float col[4];
                                static int combo = 0;

                                ImGui::Checkbox("Enabled", &enabled);
                                ImGui::SliderInt("Field of view", &fov_slider, 0, 180, "%d%");
                                ImGui::Checkbox("Silent aim", &enabled);
                                ImGui::Checkbox("Team check", &enabled);
                                ImGui::Checkbox("Auto fire", &enabled);
                                ImGui::Checkbox("Auto scope", &enabled);
                                ImGui::Checkbox("Override resolver", &enabled);
                               
                            }
                            custom::end_child( );
                        }
                        ImGui::EndGroup( );
                        ImGui::SameLine( 0, 15 );
                        ImGui::BeginGroup( );
                        {
                            custom::begin_child( "Accuracy settings", { ( ImGui::GetWindowWidth( ) - 30 ) / 2 - ImGui::GetStyle( ).ItemSpacing.x / 2, 0 } );
                            {
                                static bool enabled = false;
                                static int hitchance_slider = 0;
                                static int minimum_damage_slider = 0;
                                static int autostop_modifiers_combobox = 0;
                                static int combo = 0;
                                static char text[64];
                                static float col[4];

                                ImGui::SliderInt("Hitchance", &hitchance_slider, 0, 100, "%d%");
                                ImGui::SliderInt("Minimum damage", &minimum_damage_slider, 0, 130, "%d%");
                                ImGui::Combo("Autostop modifiers", &autostop_modifiers_combobox, "None\0\rEarly\0\rIn air\0\rBetween shots\0\rForce accuracy");
                              
                            }
                            custom::end_child( );

                            custom::begin_child( "Target settings", { ( ImGui::GetWindowWidth( ) - 30 ) / 2 - ImGui::GetStyle( ).ItemSpacing.x / 2, 0 } );
                            {
                                static bool enabled = false;
                                static int head_pointscale_slider = 0;
                                static int body_pointscale_slider = 0;
                                static int Hitboxes = 0;
                                static int Multipoint_hitboxes = 0;
                                static char text[64];
                                static float col[4];

                                ImGui::Combo("Hitboxes", &Hitboxes, "Head\0\rUpper chest\0\rChest\0\rLower chest\0\rStomach\0\rArms\0\rPelvis\0\rLegs\0\rFeet");
                                ImGui::Combo("Multipoint hitboxes", &Multipoint_hitboxes, "Head\0\rUpper chest\0\rChest\0\rLower chest\0\rStomach\0\rArms\0\rPelvis\0\rLegs\0\rFeet");
                                ImGui::SliderInt("Head pointscale", &head_pointscale_slider, 0, 100, "%d%");
                                ImGui::SliderInt("Body pointscale", &body_pointscale_slider, 0, 100, "%d%");
                            }
                            custom::end_child( );
                        }
                        ImGui::EndGroup( );
                        ImGui::Spacing( );
                    }
                    ImGui::EndChild( );
                }
                      break;
                }
            }
            ImGui::EndChild( );

            ImGui::EndGroup( );
            ImGui::PopStyleVar( );
            ImGui::PopItemFlag( );
