using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using CapturaLora.Models;

namespace CapturaLora.Data
{
    public class CapturaLoraContext : DbContext
    {
        public CapturaLoraContext (DbContextOptions<CapturaLoraContext> options)
            : base(options)
        {
        }

        public DbSet<CapturaLora.Models.UpLink> UpLink { get; set; }
    }
}
