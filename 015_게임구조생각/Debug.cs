using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _015_게임구조생각
{

    internal static class Debug
    {
        public enum LogType
        {
            Info,
            Warning,
            Error
        }

        private static List<(LogType type, string text)> LogList
            = new List<(LogType type, string text)>();

        public static void Log(LogType type, string text)
        {
            LogList.Add((type, text));
        }

        public static void PrintLog()
        {
            foreach ((LogType type,string text) log in LogList)
            {
                if (log.type == LogType.Info)
                {
                    //print
                }
                // 등등
            }
        }
    }
}
