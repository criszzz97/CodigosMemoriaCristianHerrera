using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace CapturaLora.Models
{
    public class ApplicationIds
    {
        public Int64 Id { get; set; }
        public string application_id { get; set; }
    }

    public class EndDeviceIds
    {
        public Int64 Id { get; set; }
        public string device_id { get; set; }
        public ApplicationIds application_ids { get; set; }
        public string dev_eui { get; set; }
        public string join_eui { get; set; }
        public string dev_addr { get; set; }
    }

    public class Lora
    {
        public Int64 Id { get; set; }
        public int bandwidth { get; set; }
        public int spreading_factor { get; set; }
    }

    public class DataRate
    {
        public Int64 Id { get; set; }
        public Lora lora { get; set; }
    }

    public class Settings
    {
        public Int64 Id { get; set; }
        public DataRate data_rate { get; set; }
        public int data_rate_index { get; set; }
        public string coding_rate { get; set; }
        public string frequency { get; set; }
    }

    public class User
    {
        public Int64 Id { get; set; }
        public double latitude { get; set; }
        public double longitude { get; set; }
        public int altitude { get; set; }
        public string source { get; set; }
    }

    public class Locations
    {
        public Int64 Id { get; set; }
        public User user { get; set; }
    }

    public class UplinkMessage
    {
        public Int64 Id { get; set; }
        public string session_key_id { get; set; }
        public int f_cnt { get; set; }
        public int f_port { get; set; }
        public string frm_payload { get; set; }
        public Settings settings { get; set; }
        public string consumed_airtime { get; set; }
        public Locations locations { get; set; }
    }

    public class UpLink
    {
        public Int64 Id { get; set; }
        public Boolean Leido { get; set; }

        public EndDeviceIds end_device_ids { get; set; }
        public string received_at { get; set; }
        public UplinkMessage uplink_message { get; set; }
    }
}
