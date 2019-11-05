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
        [StringLength(20,ErrorMessage = "Titlul trebuie sa aiba maxim 20 de caracter")]
        public string Title { get; set; }
        [Required]
        public string Content { get; set; }
        public DateTime Date { get; set; }
        [Required]
        public int CategoryId { get; set; }
        public virtual Category category { get; set; }
    }

    public class ArticleDbContext : DbContext
    {
        public ArticleDbContext() : base("DBConnectionString") { }
        public DbSet <Article> Articles { get; set; }
    }
}