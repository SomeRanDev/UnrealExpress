#pragma once

// This will not work. (ueprop class MyComp* my_component_var;)
//
// That's because the unreal header tool that scans header files
// to find "properties" does not take into account macros.
//
// Instead of using it do this:
// 1) write "ueprop"
// 2) CTRL+Click to come here
// 3) copy paste your template of choice

#define ueprop UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
