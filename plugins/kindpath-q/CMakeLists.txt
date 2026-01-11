juce_add_plugin(KindPathQ
    COMPANY_NAME "KindPath"
    PLUGIN_MANUFACTURER_CODE Kdpt
    PLUGIN_CODE KpQ1
    FORMATS AU VST3
    PRODUCT_NAME "KindPath Q"
)

target_sources(KindPathQ PRIVATE
    PluginProcessor.cpp
    PluginEditor.cpp
)

target_link_libraries(KindPathQ PRIVATE
    kindpath_ui
    juce::juce_audio_processors
    juce::juce_audio_utils
)

target_compile_definitions(KindPathQ PRIVATE
    JUCE_VST3_CAN_REPLACE_VST2=0
)
