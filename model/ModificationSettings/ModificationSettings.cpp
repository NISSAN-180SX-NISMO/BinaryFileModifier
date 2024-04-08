#include "ModificationSettings.h"
std::string str;
#define PRINT(a) str = #a

bool isSettingsValid(const ModificationSettings &settings) {
    return !settings.sourceDirPath.isEmpty() &&
           !settings.saveDirPath.isEmpty() &&
           !settings.fileNameMask.isEmpty() &&
           !settings.fileExtensionMask.isEmpty() &&
           settings.ExecutionPeriod.isValid();
}

QString printSettings(const ModificationSettings &settings) {
    QString result = "Current settings:\n";
    result += "- Source directory path: \"" + settings.sourceDirPath + "\"\n";
    result += "- Save directory path: \"" + settings.saveDirPath + "\"\n";
    result += "- File name mask: \"" + settings.fileNameMask + "\"\n";
    result += "- File extension mask: \"" + settings.fileExtensionMask + "\"\n";
    result += QString("- Need remove source files: ") + (settings.needRemoveSourceFiles ? "true" : "false") + "\n";
    result += QString("- Collision resolution type: ") + (settings.collisionResolutionType == COLLISION_RESOLUTION_TYPE::MODIFY ? "MODIFY" : "OVERWRITE" ) + "\n";
    result += "- Execution period: " + settings.ExecutionPeriod.toString() + "\n";
    result += "- Binary operand: " + QString::number(settings.binaryOperand, 16) + "\n";
    return result;
}