//
// Created by Nathan Goller-Deitsch on 9/20/21.
//

#include "Command.h"

#include "Group.h"

const std::string Kuka::LIN::compileKRL() {
  return "LIN " + frame.compileKRL();
}
Kuka::LIN::LIN(Frame frame) : frame(frame) {}

const std::string Kuka::PTP::compileKRL() {
  return "PTP " + frame.compileKRL();
}
Kuka::PTP::PTP(Frame frame) : frame(frame) {}

Kuka::Draw2DPenUp::Draw2DPenUp() {}
const std::string Kuka::Draw2DPenUp::compileKRL() { return Kuka::LIN(Kuka::Frame(std::nullopt, std::nullopt, 425, std::nullopt, std::nullopt, std::nullopt)).compileKRL(); }


Kuka::Draw2DPenDown::Draw2DPenDown() {}
const std::string Kuka::Draw2DPenDown::compileKRL() { return Kuka::LIN(Kuka::Frame(std::nullopt, std::nullopt, 405, std::nullopt, std::nullopt, std::nullopt)).compileKRL(); }

Kuka::Draw2DLine::Draw2DLine(float x1, float y1, float x2, float y2)
    : x1(x1), y1(y1), x2(x2), y2(y2) {}

const std::string Kuka::Draw2DLine::compileKRL() {
  Kuka::Group line;
  line.commands.emplace_back(new Kuka::LIN(Kuka::Frame(x1,y1,std::nullopt,std::nullopt,std::nullopt,std::nullopt)));
  line.commands.emplace_back(new Kuka::Draw2DPenDown());
  line.commands.emplace_back(new Kuka::LIN(Kuka::Frame(x2,y2,std::nullopt,std::nullopt,std::nullopt,std::nullopt)));
  line.commands.emplace_back(new Kuka::Draw2DPenUp());
  return line.compileKRL();
}

const std::string Kuka::STARTWRAPPER::compileKRL() { return  "&ACCESS RVP\n"
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
                                                             ";Params IlfProvider=kukaroboter.basistech.inlineforms.movement.spline; Kuka.IsGlobalPoint=False; Kuka.PointName=HOME; Kuka.BlendingEnabled=False; Kuka.MoveDataPtpName=DEFAULT; Kuka.VelocityPtp=100; Kuka.VelocityFieldEnabled=True; Kuka.CurrentCDSetIndex=0; Kuka.MovementParameterFieldEnabled=True; IlfCommand=SPTP\n"
                                                             ";ENDFOLD\n"
                                                             "SPTP XHOME WITH $VEL_AXIS[1] = SVEL_JOINT(100.0), $TOOL = STOOL2(FHOME), $BASE = SBASE(FHOME.BASE_NO), $IPO_MODE = SIPO_MODE(FHOME.IPO_FRAME), $LOAD = SLOAD(FHOME.TOOL_NO), $ACC_AXIS[1] = SACC_JOINT(PDEFAULT), $APO = SAPO_PTP(PDEFAULT), $GEAR_JERK[1] = SGEAR_JERK(PDEFAULT), $COLLMON_TOL_PRO[1] = USE_CM_PRO_VALUES(0)\n"
                                                             ";ENDFOLD\n"; }
const std::string Kuka::ENDWRAPPER::compileKRL() { return ";FOLD SPTP HOME Vel=100 % DEFAULT ;%{PE}\n"
                                                   ";FOLD Parameters ;%{h}\n"
                                                   ";Params IlfProvider=kukaroboter.basistech.inlineforms.movement.spline; Kuka.IsGlobalPoint=False; Kuka.PointName=HOME; Kuka.BlendingEnabled=False; Kuka.MoveDataPtpName=DEFAULT; Kuka.VelocityPtp=100; Kuka.VelocityFieldEnabled=True; Kuka.CurrentCDSetIndex=0; Kuka.MovementParameterFieldEnabled=True; IlfCommand=SPTP\n"
                                                   ";ENDFOLD\n"
                                                   "SPTP XHOME WITH $VEL_AXIS[1] = SVEL_JOINT(100.0), $TOOL = STOOL2(FHOME), $BASE = SBASE(FHOME.BASE_NO), $IPO_MODE = SIPO_MODE(FHOME.IPO_FRAME), $LOAD = SLOAD(FHOME.TOOL_NO), $ACC_AXIS[1] = SACC_JOINT(PDEFAULT), $APO = SAPO_PTP(PDEFAULT), $GEAR_JERK[1] = SGEAR_JERK(PDEFAULT), $COLLMON_TOL_PRO[1] = USE_CM_PRO_VALUES(0)\n"
                                                   ";ENDFOLD\n"
                                                   "\n"
                                                   "END"; }
