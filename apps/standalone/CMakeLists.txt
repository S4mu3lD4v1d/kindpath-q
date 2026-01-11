juce_add_gui_app(KindPathQStandalone
    PRODUCT_NAME "KindPath Q"
    BUNDLE_ID "com.kindpath.q.standalone"
)

target_sources(KindPathQStandalone PRIVATE
    Main.cpp
)

target_link_libraries(KindPathQStandalone PRIVATE
    kindpath_ui
    juce::juce_audio_utils
    juce::juce_audio_devices
    juce::juce_gui_extra
)

target_compile_definitions(KindPathQStandalone PRIVATE
    JUCE_APPLICATION_NAME_STRING="KindPath Q"
    JUCE_APPLICATION_VERSION_STRING="0.1.0"
)
