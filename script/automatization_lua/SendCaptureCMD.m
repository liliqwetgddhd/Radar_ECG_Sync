function SendCaptureCMD
    %% 本文件用于 MATLAB发送指令给mmwave studio，控制DCA采集并回传数据
    
    %% 保存文件路径设置
    % data_path为bin文件的保存文件夹，bin_name为设置的bin文件名(不含.bin，如\\adc_data_1)

    data_path = 'D:\\software\\temporary\\DatasetFile\\Action';
    
    bin_name = '\\adc_data_test'; % 实际文件会产生Raw_0的后缀
    
    % 检查文件夹是否存在，如果不存在则创建
    if ~isfolder(data_path)
        mkdir(data_path);
    end    
    
    %% 修改采集数据的脚本文件
    % 设计bin文件目录
    str1 = strcat('adc_data_path="',data_path, bin_name,'.bin"'); 
    
    str = [str1,"ar1.CaptureCardConfig_StartRecord(adc_data_path, 1)","RSTD.Sleep(1000)","ar1.StartFrame()"];
    fid = fopen('D:\software\major\ti\mmwave_studio\install\mmwave_studio_02_01_01_00\mmWaveStudio\Scripts\FrameStart.lua','w');
    for i = 1:length(str)
        fprintf(fid,'%s\n',str(i));
    end
    fclose(fid); % 关闭文件
    
    %% 配置雷达数据采集
    addpath(genpath('.\'))
    % Initialize mmWaveStudio .NET connection
    RSTD_DLL_Path = 'D:\software\major\ti\mmwave_studio\install\mmwave_studio_02_01_01_00\mmWaveStudio\Clients\RtttNetClientController\RtttNetClientAPI.dll';
    ErrStatus = Init_RSTD_Connection(RSTD_DLL_Path);
    if (ErrStatus ~= 30000)
        disp('Error inside Init_RSTD_Connection');
        return;
    end
    strFilename = 'D:\\software\\major\\ti\\mmwave_studio\\install\\mmwave_studio_02_01_01_00\\mmWaveStudio\\Scripts\\FrameStart.lua';
    Lua_String = sprintf('dofile("%s")',strFilename);
    ErrStatus = RtttNetClientAPI.RtttNetClient.SendCommand(Lua_String);
    
    %% 打印bin文件保存路径
    new_data_path = regexprep(data_path, '\\\\', '\');
    new_bin_name = regexprep(bin_name, '\\\\', '\');    
    fprintf('----\n开始采集雷达数据！\nbin文件保存路径:\n');
    disp(['"',new_data_path, new_bin_name,'_Raw_0.bin"']);
    fprintf('---------------------------\n\n');
end


