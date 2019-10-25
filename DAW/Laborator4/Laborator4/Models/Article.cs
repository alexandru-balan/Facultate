using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Data.Entity;
using System.Linq;
using System.Web;

namespace Laborator4.Models
{
    public class Article
    {
        [Key]
        public int Id { get; set; }
        [Required]
        public string Title { get; set; }
        [Required]
        public string Content { get; set; }
        public DateTime Date { get; set; }
        public int CategoryId { get; set; }
        public virtual Category category { get; set; }
    }

    public class ArticleDbContext : DbContext
    {
        public ArticleDbContext() : base("DBConnectionString") { }
        public DbSet <Article> Articles { get; set; }
    }
}