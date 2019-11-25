using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Data.Entity;
using System.Linq;
using System.Web;

namespace ArticleCategory.Models
{
    public class Article
    {
        public string UserId {get; set;}
        public virtual ApplicationUser User { get; set; }

        [Key]
        public int Id { get; set; }
        [Required(ErrorMessage = "Titlul e obligatoriu")]
        [StringLength(20,ErrorMessage = "Titlul trebuie sa aiba maxim 20 de caracter")]
        public string Title { get; set; }
        [Required(ErrorMessage = "Continutul e obligatoriu")]
        public string Content { get; set; }
        public DateTime Date { get; set; }
        [Required]
        public int CategoryId { get; set; }
        public virtual Category category { get; set; }
    }
}