-------------------------------------------------------------------------------
-- system_v_scaler_0_wrapper.vhd
-------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

library UNISIM;
use UNISIM.VCOMPONENTS.ALL;

library v_scaler_v7_01_a;
use v_scaler_v7_01_a.all;

entity system_v_scaler_0_wrapper is
  port (
    core_clk : in std_logic;
    core_aresetn : in std_logic;
    irq : out std_logic;
    intc_if : out std_logic_vector(31 downto 0);
    s_axi_aclk : in std_logic;
    s_axi_aresetn : in std_logic;
    s_axi_awaddr : in std_logic_vector(8 downto 0);
    s_axi_awvalid : in std_logic;
    s_axi_awready : out std_logic;
    s_axi_wdata : in std_logic_vector(31 downto 0);
    s_axi_wstrb : in std_logic_vector(3 downto 0);
    s_axi_wvalid : in std_logic;
    s_axi_wready : out std_logic;
    s_axi_bresp : out std_logic_vector(1 downto 0);
    s_axi_bvalid : out std_logic;
    s_axi_bready : in std_logic;
    s_axi_araddr : in std_logic_vector(8 downto 0);
    s_axi_arvalid : in std_logic;
    s_axi_arready : out std_logic;
    s_axi_rdata : out std_logic_vector(31 downto 0);
    s_axi_rresp : out std_logic_vector(1 downto 0);
    s_axi_rvalid : out std_logic;
    s_axi_rready : in std_logic;
    s_axis_video_aclk : in std_logic;
    s_axis_video_tvalid : in std_logic;
    s_axis_video_tlast : in std_logic;
    s_axis_video_tuser : in std_logic;
    s_axis_video_tdata : in std_logic_vector(15 downto 0);
    s_axis_video_tready : out std_logic;
    s_axis_video_aresetn : in std_logic;
    m_axis_video_aclk : in std_logic;
    m_axis_video_tvalid : out std_logic;
    m_axis_video_tlast : out std_logic;
    m_axis_video_tuser : out std_logic;
    m_axis_video_tdata : out std_logic_vector(15 downto 0);
    m_axis_video_tready : in std_logic;
    m_axis_video_aresetn : in std_logic
  );

  attribute x_core_info : STRING;
  attribute x_core_info of system_v_scaler_0_wrapper : entity is "v_scaler_v7_01_a";

end system_v_scaler_0_wrapper;

architecture STRUCTURE of system_v_scaler_0_wrapper is

  component v_scaler is
    generic (
      C_HAS_AXI4_LITE : INTEGER;
      C_HAS_IRQ : INTEGER;
      C_HAS_INTC_IF : INTEGER;
      C_HAS_DEBUG : INTEGER;
      C_CHROMA_FORMAT : INTEGER;
      C_NUM_CHANNELS : INTEGER;
      C_S_AXIS_VIDEO_DATA_WIDTH : INTEGER;
      C_S_AXIS_VIDEO_TDATA_WIDTH : INTEGER;
      C_M_AXIS_VIDEO_DATA_WIDTH : INTEGER;
      C_M_AXIS_VIDEO_TDATA_WIDTH : INTEGER;
      C_TGT_CORE_CLK_FREQ : INTEGER;
      C_NUM_H_TAPS : INTEGER;
      C_NUM_V_TAPS : INTEGER;
      C_MAX_SAMPLES_IN_PER_LINE : INTEGER;
      C_MAX_SAMPLES_OUT_PER_LINE : INTEGER;
      C_MAX_LINES_IN_PER_FRAME : INTEGER;
      C_MAX_LINES_OUT_PER_FRAME : INTEGER;
      C_MAX_PHASES : INTEGER;
      C_MAX_COEF_SETS : INTEGER;
      C_MIF : STRING;
      C_ELABORATION_DIR : STRING;
      C_AUTO_HW_CONFIG : INTEGER;
      C_MANUAL_HWC_VAL : INTEGER;
      C_SEPARATE_YC_COEFS : INTEGER;
      C_SEPARATE_HV_COEFS : INTEGER;
      C_TARGET_MAX_FRAME_RATE : INTEGER;
      C_S_AXI_ADDR_WIDTH : INTEGER;
      C_S_AXI_DATA_WIDTH : INTEGER;
      C_S_AXI_CLK_FREQ_HZ : INTEGER;
      C_NUM_H_PHASES : INTEGER;
      C_NUM_V_PHASES : INTEGER;
      C_SOURCE_H_SIZE : INTEGER;
      C_SOURCE_V_SIZE : INTEGER;
      C_APERTURE_START_PIXEL : INTEGER;
      C_APERTURE_END_PIXEL : INTEGER;
      C_APERTURE_START_LINE : INTEGER;
      C_APERTURE_END_LINE : INTEGER;
      C_OUTPUT_H_SIZE : INTEGER;
      C_OUTPUT_V_SIZE : INTEGER;
      C_HSF : INTEGER;
      C_VSF : INTEGER;
      C_FAMILY : STRING
    );
    port (
      core_clk : in std_logic;
      core_aresetn : in std_logic;
      irq : out std_logic;
      intc_if : out std_logic_vector(31 downto 0);
      s_axi_aclk : in std_logic;
      s_axi_aresetn : in std_logic;
      s_axi_awaddr : in std_logic_vector((C_S_AXI_ADDR_WIDTH-1) downto 0);
      s_axi_awvalid : in std_logic;
      s_axi_awready : out std_logic;
      s_axi_wdata : in std_logic_vector((C_S_AXI_DATA_WIDTH-1) downto 0);
      s_axi_wstrb : in std_logic_vector(((C_S_AXI_DATA_WIDTH/8)-1) downto 0);
      s_axi_wvalid : in std_logic;
      s_axi_wready : out std_logic;
      s_axi_bresp : out std_logic_vector(1 downto 0);
      s_axi_bvalid : out std_logic;
      s_axi_bready : in std_logic;
      s_axi_araddr : in std_logic_vector((C_S_AXI_ADDR_WIDTH-1) downto 0);
      s_axi_arvalid : in std_logic;
      s_axi_arready : out std_logic;
      s_axi_rdata : out std_logic_vector((C_S_AXI_DATA_WIDTH-1) downto 0);
      s_axi_rresp : out std_logic_vector(1 downto 0);
      s_axi_rvalid : out std_logic;
      s_axi_rready : in std_logic;
      s_axis_video_aclk : in std_logic;
      s_axis_video_tvalid : in std_logic;
      s_axis_video_tlast : in std_logic;
      s_axis_video_tuser : in std_logic;
      s_axis_video_tdata : in std_logic_vector(C_S_AXIS_VIDEO_TDATA_WIDTH-1 downto 0);
      s_axis_video_tready : out std_logic;
      s_axis_video_aresetn : in std_logic;
      m_axis_video_aclk : in std_logic;
      m_axis_video_tvalid : out std_logic;
      m_axis_video_tlast : out std_logic;
      m_axis_video_tuser : out std_logic;
      m_axis_video_tdata : out std_logic_vector(C_M_AXIS_VIDEO_TDATA_WIDTH-1 downto 0);
      m_axis_video_tready : in std_logic;
      m_axis_video_aresetn : in std_logic
    );
  end component;

begin

  v_scaler_0 : v_scaler
    generic map (
      C_HAS_AXI4_LITE => 1,
      C_HAS_IRQ => 1,
      C_HAS_INTC_IF => 0,
      C_HAS_DEBUG => 0,
      C_CHROMA_FORMAT => 2,
      C_NUM_CHANNELS => 2,
      C_S_AXIS_VIDEO_DATA_WIDTH => 8,
      C_S_AXIS_VIDEO_TDATA_WIDTH => 16,
      C_M_AXIS_VIDEO_DATA_WIDTH => 8,
      C_M_AXIS_VIDEO_TDATA_WIDTH => 16,
      C_TGT_CORE_CLK_FREQ => 148,
      C_NUM_H_TAPS => 4,
      C_NUM_V_TAPS => 4,
      C_MAX_SAMPLES_IN_PER_LINE => 1920,
      C_MAX_SAMPLES_OUT_PER_LINE => 1920,
      C_MAX_LINES_IN_PER_FRAME => 1080,
      C_MAX_LINES_OUT_PER_FRAME => 1080,
      C_MAX_PHASES => 11,
      C_MAX_COEF_SETS => 1,
      C_MIF => "v_scaler_0.mif",
      C_ELABORATION_DIR => "C:\tmp\MP-2\system\hdl\/elaborate/v_scaler_0_v7_01_a/",
      C_AUTO_HW_CONFIG => 1,
      C_MANUAL_HWC_VAL => 6,
      C_SEPARATE_YC_COEFS => 0,
      C_SEPARATE_HV_COEFS => 1,
      C_TARGET_MAX_FRAME_RATE => 60,
      C_S_AXI_ADDR_WIDTH => 9,
      C_S_AXI_DATA_WIDTH => 32,
      C_S_AXI_CLK_FREQ_HZ => 100000000,
      C_NUM_H_PHASES => 4,
      C_NUM_V_PHASES => 4,
      C_SOURCE_H_SIZE => 1920,
      C_SOURCE_V_SIZE => 1080,
      C_APERTURE_START_PIXEL => 0,
      C_APERTURE_END_PIXEL => 1919,
      C_APERTURE_START_LINE => 0,
      C_APERTURE_END_LINE => 1079,
      C_OUTPUT_H_SIZE => 1920,
      C_OUTPUT_V_SIZE => 1080,
      C_HSF => 1048576,
      C_VSF => 1048576,
      C_FAMILY => "zynq"
    )
    port map (
      core_clk => core_clk,
      core_aresetn => core_aresetn,
      irq => irq,
      intc_if => intc_if,
      s_axi_aclk => s_axi_aclk,
      s_axi_aresetn => s_axi_aresetn,
      s_axi_awaddr => s_axi_awaddr,
      s_axi_awvalid => s_axi_awvalid,
      s_axi_awready => s_axi_awready,
      s_axi_wdata => s_axi_wdata,
      s_axi_wstrb => s_axi_wstrb,
      s_axi_wvalid => s_axi_wvalid,
      s_axi_wready => s_axi_wready,
      s_axi_bresp => s_axi_bresp,
      s_axi_bvalid => s_axi_bvalid,
      s_axi_bready => s_axi_bready,
      s_axi_araddr => s_axi_araddr,
      s_axi_arvalid => s_axi_arvalid,
      s_axi_arready => s_axi_arready,
      s_axi_rdata => s_axi_rdata,
      s_axi_rresp => s_axi_rresp,
      s_axi_rvalid => s_axi_rvalid,
      s_axi_rready => s_axi_rready,
      s_axis_video_aclk => s_axis_video_aclk,
      s_axis_video_tvalid => s_axis_video_tvalid,
      s_axis_video_tlast => s_axis_video_tlast,
      s_axis_video_tuser => s_axis_video_tuser,
      s_axis_video_tdata => s_axis_video_tdata,
      s_axis_video_tready => s_axis_video_tready,
      s_axis_video_aresetn => s_axis_video_aresetn,
      m_axis_video_aclk => m_axis_video_aclk,
      m_axis_video_tvalid => m_axis_video_tvalid,
      m_axis_video_tlast => m_axis_video_tlast,
      m_axis_video_tuser => m_axis_video_tuser,
      m_axis_video_tdata => m_axis_video_tdata,
      m_axis_video_tready => m_axis_video_tready,
      m_axis_video_aresetn => m_axis_video_aresetn
    );

end architecture STRUCTURE;

