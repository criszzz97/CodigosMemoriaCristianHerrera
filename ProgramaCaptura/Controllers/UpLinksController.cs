using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using CapturaLora.Data;
using CapturaLora.Models;

namespace CapturaLora.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class UpLinksController : ControllerBase
    {
        private readonly CapturaLoraContext _context;

        public UpLinksController(CapturaLoraContext context)
        {
            _context = context;
        }

        // GET: api/UpLinks
        [HttpGet]
        public async Task<ActionResult<IEnumerable<UpLink>>> GetUpLink()
        {
            return await _context.UpLink.ToListAsync();
        }

        // GET: api/UpLinks/5
        [HttpGet("{id}")]
        public async Task<ActionResult<UpLink>> GetUpLink(long id)
        {
            var upLink = await _context.UpLink.FindAsync(id);

            if (upLink == null)
            {
                return NotFound();
            }

            return upLink;
        }

        // PUT: api/UpLinks/5
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPut("{id}")]
        public async Task<IActionResult> PutUpLink(long id, UpLink upLink)
        {
            if (id != upLink.Id)
            {
                return BadRequest();
            }

            _context.Entry(upLink).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!UpLinkExists(id))
                {
                    return NotFound();
                }
                else
                {
                    throw;
                }
            }

            return NoContent();
        }

        // POST: api/UpLinks
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPost]
        public async Task<ActionResult<UpLink>> PostUpLink(UpLink upLink)
        {
            _context.UpLink.Add(upLink);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetUpLink", new { id = upLink.Id }, upLink);
        }

        // DELETE: api/UpLinks/5
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteUpLink(long id)
        {
            var upLink = await _context.UpLink.FindAsync(id);
            if (upLink == null)
            {
                return NotFound();
            }

            _context.UpLink.Remove(upLink);
            await _context.SaveChangesAsync();

            return NoContent();
        }

        private bool UpLinkExists(long id)
        {
            return _context.UpLink.Any(e => e.Id == id);
        }
    }
}
