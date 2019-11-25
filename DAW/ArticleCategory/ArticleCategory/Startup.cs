using ArticleCategory.Models;
using Microsoft.AspNet.Identity;
using Microsoft.AspNet.Identity.EntityFramework;
using Microsoft.Owin;
using Owin;

[assembly: OwinStartupAttribute(typeof(ArticleCategory.Startup))]
namespace ArticleCategory
{
    public partial class Startup
    {
        public void Configuration(IAppBuilder app)
        {
            ConfigureAuth(app);

            createAdminAndAppRoles();
        }

        private void createAdminAndAppRoles()
        {
            ApplicationDbContext context = new ApplicationDbContext();

            var roleManager = new RoleManager<IdentityRole>(new RoleStore<IdentityRole>(context));
            var userManager = new UserManager<ApplicationUser>(new UserStore<ApplicationUser>(context));

            // Se adauga rolurile aplicatiei
            if (!roleManager.RoleExists("Administrator"))
            {
                // Se adauga rolul de admin
                var role = new IdentityRole();
                role.Name = "Administrator";
                roleManager.Create(role);

                // Se adauga userul admin
                var user = new ApplicationUser();
                user.UserName = "ab@unibuc.com";
                user.Email = "ab@unibuc.com";
                var adminCreated = userManager.Create(user, "Administrator");
                if (adminCreated.Succeeded)
                {
                    userManager.AddToRole(user.Id, "Administrator");
                }
            }

            if (!roleManager.RoleExists("Editor"))
            {
                var role = new IdentityRole();
                role.Name = "Editor";
                roleManager.Create(role);
            }

            if (!roleManager.RoleExists("User"))
            {
                var role = new IdentityRole();
                role.Name = "User";
                roleManager.Create(role);
            }

        }
    }
}
