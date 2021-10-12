//
// Created by Nathan Goller-Deitsch on 9/20/21.
//

#include "Command.h"

#include "Group.h"

const std::string Kaironetic::LIN::compileKRL() {
  return "LIN " + frame.compileKRL();
}
Kaironetic::LIN::LIN(Frame frame) : frame(frame) {}

const std::string Kaironetic::PTP::compileKRL() {
  return "PTP " + frame.compileKRL();
}
Kaironetic::PTP::PTP(Frame frame) : frame(frame) {

}
const std::string Kaironetic::SPL::compileKRL() {
  return "SPL " + frame.compileKRL();
}
Kaironetic::SPL::SPL(Frame frame) : frame(frame) {

}
const std::string Kaironetic::SPLINE::compileKRL() {
  return "SPLINE";
}
const std::string Kaironetic::ENDSPLINE::compileKRL() {
  return "ENDSPLINE";
}
const std::string Kaironetic::STARTWRAPPER::compileKRL() {
  return "&ACCESS RVP\n"
         "&REL 17\n"
         "&PARAM EDITMASK = *\n"
         "&PARAM TEMPLATE = C:\\KRC\\Roboter\\Template\\vorgabe\n"
         "&PARAM DISKPATH = KRC:\\R1\\Group\n"
         "DEF synth_out( )\n"
         ";FOLD INI;%{PE}\n"
         "  ;FOLD BASISTECH INI\n"
         "    GLOBAL INTERRUPT DECL 3 WHEN $STOPMESS==TRUE DO IR_STOPM ( )\n"
         "    INTERRUPT ON 3 \n"
         "    BAS (#INITMOV,0 )\n"
         "  ;ENDFOLD (BASISTECH INI)\n"
         "  ;FOLD USER INI\n"
         "    ;Make your modifications here\n"
         "\n"
         "  ;ENDFOLD (USER INI)\n"
         ";ENDFOLD (INI)\n"
         "\n"
         ";FOLD SPTP HOME Vel=100 % DEFAULT ;%{PE}\n"
         ";FOLD Parameters ;%{h}\n"
         ";Params "
         "IlfProvider=kukaroboter.basistech.inlineforms.movement.spline; "
         "Kuka.IsGlobalPoint=False; Kuka.PointName=HOME; "
         "Kuka.BlendingEnabled=False; Kuka.MoveDataPtpName=DEFAULT; "
         "Kuka.VelocityPtp=100; Kuka.VelocityFieldEnabled=True; "
         "Kuka.CurrentCDSetIndex=0; Kuka.MovementParameterFieldEnabled=True; "
         "IlfCommand=SPTP\n"
         ";ENDFOLD\n"
         "SPTP XHOME WITH $VEL_AXIS[1] = SVEL_JOINT(100.0), $TOOL = "
         "STOOL2(FHOME), $BASE = SBASE(FHOME.BASE_NO), $IPO_MODE = "
         "SIPO_MODE(FHOME.IPO_FRAME), $LOAD = SLOAD(FHOME.TOOL_NO), "
         "$ACC_AXIS[1] = SACC_JOINT(PDEFAULT), $APO = SAPO_PTP(PDEFAULT), "
         "$GEAR_JERK[1] = SGEAR_JERK(PDEFAULT), $COLLMON_TOL_PRO[1] = "
         "USE_CM_PRO_VALUES(0)\n"
         ";ENDFOLD\n"
         "$VEL.CP=0.2";
}
const std::string Kaironetic::ENDWRAPPER::compileKRL() {
  return ";FOLD SPTP HOME Vel=100 % DEFAULT ;%{PE}\n"
         ";FOLD Parameters ;%{h}\n"
         ";Params "
         "IlfProvider=kukaroboter.basistech.inlineforms.movement.spline; "
         "Kuka.IsGlobalPoint=False; Kuka.PointName=HOME; "
         "Kuka.BlendingEnabled=False; Kuka.MoveDataPtpName=DEFAULT; "
         "Kuka.VelocityPtp=100; Kuka.VelocityFieldEnabled=True; "
         "Kuka.CurrentCDSetIndex=0; Kuka.MovementParameterFieldEnabled=True; "
         "IlfCommand=SPTP\n"
         ";ENDFOLD\n"
         "SPTP XHOME WITH $VEL_AXIS[1] = SVEL_JOINT(100.0), $TOOL = "
         "STOOL2(FHOME), $BASE = SBASE(FHOME.BASE_NO), $IPO_MODE = "
         "SIPO_MODE(FHOME.IPO_FRAME), $LOAD = SLOAD(FHOME.TOOL_NO), "
         "$ACC_AXIS[1] = SACC_JOINT(PDEFAULT), $APO = SAPO_PTP(PDEFAULT), "
         "$GEAR_JERK[1] = SGEAR_JERK(PDEFAULT), $COLLMON_TOL_PRO[1] = "
         "USE_CM_PRO_VALUES(0)\n"
         ";ENDFOLD\n"
         "\n"
         "END";
}
Kaironetic::Comment::Comment(const std::string comment) : comment(comment) {}
const std::string Kaironetic::Comment::compileKRL() {
  return std::string("; " + comment);
}
